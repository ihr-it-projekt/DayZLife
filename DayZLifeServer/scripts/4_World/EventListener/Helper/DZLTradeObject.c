class DZLTradeObject {
    int sum = 0;
    int taxSum = 0;
    string error = "";
    ref array<DZLTraderType> typesToBuy = new array<DZLTraderType>;
    DZLBankingConfig bankConfig = DZLConfig.Get().bankConfig;
    ref DZLTraderStorage traderStorage = DZLDatabaseLayer.Get().GetTraderStorage();
    ref DZLBank bank = DZLDatabaseLayer.Get().GetBank();
    ref DZLTraderConfig traderConfig = DZLConfig.Get().traderConfig;
    ref map<string, int> buyLogs = new map<string, int>;
    ref map<string, int> sellLogs = new map<string, int>;
    ref map<string, ref DZLTraderTypeStorage> storageToSave = new map<string, ref DZLTraderTypeStorage>;

    PlayerBase player;
    PlayerIdentity playerIdentity;
    string playerId;
    ref array<EntityAI> entitiesToSell;
    ref array<string> itemsToBuy;
    ref array<EntityAI> playerItems;
    ref DZLTraderPosition traderPosition;
    ref DZLPlayer dzlPlayer;

    void DZLTradeObject(PlayerBase _player, ref array<EntityAI> _itemsToSell, ref array<string> _itemsToBuy, ref DZLTraderPosition _traderPosition) {
        player = _player;
        playerItems = player.GetPlayerItems();
        playerIdentity = player.GetIdentity();
        playerId = playerIdentity.GetId();
        dzlPlayer = player.GetDZLPlayer();
        itemsToBuy = _itemsToBuy;
        entitiesToSell = _itemsToSell;
        traderPosition = _traderPosition;
    }

    bool CanTrade() {
        if(error) {
            SendTraderResponse();
            return false;
        }

        if(typesToBuy.Count() == 0 && entitiesToSell.Count() == 0) {
            error = "#you_have_to_trade_minimum_one_item";
            SendTraderResponse();
            return false;
        }
        if(typesToBuy.Count() != itemsToBuy.Count() && sellLogs.Count() != entitiesToSell.Count()) {
            error = "#not_all_items_found_that_you_want_to_trade";
            SendTraderResponse();
            return false;
        }

        if(!dzlPlayer.HasEnoughMoney(sum)) {
            error = "#error_not_enough_money";
            SendTraderResponse();
            return false;
        }

        return true;
    }

    void CheckCategories() {
        foreach(string categoryName: traderPosition.categoryNames) {
            DZLTraderCategory category = traderConfig.categories.GetCatByName(categoryName);
            if(!category) continue;
            CheckCategory(category);
            if(error) return;
        }
    }

    void CheckCategory(DZLTraderCategory category) {
        foreach(string typeId: itemsToBuy) {
            CheckItemToBuy(typeId, category);
            if(error) return;
        }
        foreach(EntityAI item: entitiesToSell) {
            CheckItemsToSell(item, category);
            if(error) return;
        }
    }

    void CheckItemToBuy(string typeId, DZLTraderCategory category) {
        DZLTraderType traderType = category.GetItemById(typeId);
        if(!traderType) return;

        DZLTraderTypeStorage storage = CheckStorageBuy(traderType.type);
        if(error) return;

        typesToBuy.Insert(traderType);
        sum += traderType.CalculateDynamicBuyPrice(storage);

        if(!storage) return;

        storage.StorageDown();
        storageToSave.Insert(traderType.type, storage);
    }

    DZLTraderTypeStorage CheckStorageBuy(string type) {
        DZLTraderTypeStorage storage = traderStorage.GetCurrentStorageByName(type);
        if(!storage) return null;

        if(storage.IsStorageBelowZero()) {
            error = "#you_buy_too_much";
            return null;
        }

        return storage;
    }

    void CheckItemsToSell(EntityAI item, DZLTraderCategory category) {
        if(!item) return;
        CarScript carsScript = CarScript.Cast(item);
        if(carsScript && carsScript.ownerId != playerId) return;

        DZLTraderType traderType = category.GetItemByType(item.GetType());
        if(!traderType) return;

        DZLTraderTypeStorage storage = CheckStorageSell(item);
        if(error) return;

        float itemPrice = traderType.CalculateDynamicSellPrice(storage);
        itemPrice = DZLTraderHelper.GetQuantityPrice(itemPrice, item);

        float itemTax = itemPrice / 100 * bankConfig.sellTradingTax;
        sum -= Math.Round(itemPrice - itemTax);
        taxSum += Math.Round(itemTax);

        sellLogs.Insert(traderType.type, itemPrice);

        if(!storage) return;
        storage.StorageUp(DZLTraderHelper.GetQuantity(item));
        storageToSave.Insert(item.GetType(), storage);
    }

    DZLTraderTypeStorage CheckStorageSell(EntityAI item) {
        DZLTraderTypeStorage storage = traderStorage.GetCurrentStorageByName(item.GetType());
        if(!storage) return null;

        if(storage.IsStorageOverFilled()) {
            error = "#you_sell_too_much";
            return null;
        }

        return storage;
    }


    void SendTraderResponse() {
        string message = "#trade_was_successful";

        if(error) message = error;

        g_Game.RPCSingleParam(player, DZL_RPC.TRADE_ACTION_RESPONSE, new Param1<string>(message), true, playerIdentity);
        g_Game.RPCSingleParam(player, DZL_RPC.PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(bank), true);
        g_Game.RPCSingleParam(null, DZL_RPC.EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, playerIdentity);
    }

    void Trade() {
        dzlPlayer.AddMoneyToPlayer(sum * -1);
        bank.AddTax(taxSum);

        foreach(DZLTraderType traderType: typesToBuy) {
            buyLogs.Insert(traderType.type, traderType.buyPrice);
            Add(traderType);
        }

        foreach(EntityAI item: entitiesToSell) {
            g_Game.ObjectDelete(item);
        }
    }

    void SaveStorage() {
        foreach(DZLTraderTypeStorage storage: storageToSave) {
            storage.Save();
        }
    }

    void LogTrades() {
        foreach(string buyType, int buyPrice: buyLogs) {
            DZLLogTraderTransaction(playerId, "buy", buyType, buyPrice);
        }
        foreach(string sellType, int sellPrice: sellLogs) {
            DZLLogTraderTransaction(playerId, "sell", sellType, sellPrice);
        }
    }

    private bool Add(DZLTraderType type) {
        EntityAI item = CreateItem(type);
        if(!item) return false;

        ItemBase itemBase = ItemBase.Cast(item);
        if(DZLTraderHelper.IsStackable(item)) {
            itemBase.SetQuantity(1);
        }

        if(itemBase && itemBase.HasQuantity()) {
            int max = DZLTraderHelper.GetQuantityMax(itemBase);
            if(max > 1) itemBase.SetQuantity(max);
        }

        if(item.GetInventory()) {
            foreach(string attachment: type.attachments) {
                item.GetInventory().CreateAttachment(attachment);
            }
        }

        HandleCar(item, type);

        return true;
    }

    private EntityAI CreateItem(DZLTraderType type) {
        EntityAI item;
        if(!type.usePlayerAsSpawnPoint) {
            vector spawnPosition = traderPosition.spawnPositionOfVehicles;
            vector orientation = traderPosition.spawnOrientationOfVehicles;

            DZLZone libZone = DZLSpawnHelper.DZLSearchForFreePositionAndOrientation(spawnPosition, orientation);
            spawnPosition = libZone.position;
            orientation = libZone.orientation;

            item = EntityAI.Cast(g_Game.CreateObjectEx(type.type, spawnPosition, ECE_LOCAL | ECE_CREATEPHYSICS | ECE_TRACE));
            if(!item) return null;
            g_Game.RemoteObjectCreate(item);

            item.SetPosition(spawnPosition);
            item.SetOrientation(orientation);
            item.SetDirection(item.GetDirection());
        }

        InventoryLocation inventoryLocation = new InventoryLocation;
        if(!item && player.GetInventory().FindFirstFreeLocationForNewEntity(type.type, FindInventoryLocationType.ANY, inventoryLocation)) {
            item = player.GetHumanInventory().CreateInInventory(type.type);
        }

        if(!item && !player.GetHumanInventory().GetEntityInHands()) {
            item = player.GetHumanInventory().CreateInHands(type.type);
        }

        if(!item) {
            item = player.SpawnEntityOnGroundPos(type.type, player.GetPosition());
        }

        return item;
    }

    private void HandleCar(EntityAI item, DZLTraderType type) {
        if(!type.isCar) return;

        Car car = Car.Cast(item);
        car.Fill(CarFluid.FUEL, car.GetFluidCapacity(CarFluid.FUEL));
        car.Fill(CarFluid.OIL, car.GetFluidCapacity(CarFluid.OIL));
        car.Fill(CarFluid.BRAKE, car.GetFluidCapacity(CarFluid.BRAKE));
        car.Fill(CarFluid.COOLANT, car.GetFluidCapacity(CarFluid.COOLANT));

        car.Fill(CarFluid.USER1, car.GetFluidCapacity(CarFluid.USER1));
        car.Fill(CarFluid.USER2, car.GetFluidCapacity(CarFluid.USER2));
        car.Fill(CarFluid.USER3, car.GetFluidCapacity(CarFluid.USER3));
        car.Fill(CarFluid.USER4, car.GetFluidCapacity(CarFluid.USER4));

        car.SetLifetime(3888000);
        CarScript carScript = CarScript.Cast(car);
        if(carScript) carScript.OwnCar(player.GetIdentity(), "", "");
    }

}