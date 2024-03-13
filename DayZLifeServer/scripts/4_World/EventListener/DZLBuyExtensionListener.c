class DZLBuyExtensionListener {
    private ref DZLHouseFinder houseFinder;
    private ref DZLConfig config;

    void DZLBuyExtensionListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
        houseFinder = new DZLHouseFinder;
        config = DZLConfig.Get();

        houseFinder.SetConfig(config);
    }

    void ~DZLBuyExtensionListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DAY_Z_LIFE_BUY_EXTENSION) {
            autoptr Param2<Building, string> paramBuyStorage;
            if(ctx.Read(paramBuyStorage)) {
                PlayerBase player = PlayerBase.Cast(target);
                DZLPlayer dzlPlayer = player.GetDZLPlayer();
                DZLBuilding dzlBuilding = new DZLBuilding(paramBuyStorage.param1);
                DZLHouseDefinition actualHouseDef = houseFinder.GetHouseDefinitionByBuilding(paramBuyStorage.param1);

                DZLHouseExtension extension = config.GetHouseExtensionById(paramBuyStorage.param2);

                if(extension && dzlBuilding.IsOwner(player)) {
                    string message = "#error_buying_alarm_system";
                    int buyPriceBuy = 0;
                    if(extension.isHouseInventory) {
                        DZLHouseInventory inventory;
                        int currentLevel = 0;
                        float factor = 1.0;
                        if(dzlBuilding.HasInventory()) {
                            inventory = DZLDatabaseLayer.Get().GetHouseInventory(dzlBuilding.GetDZLHouse().GetOwner(), dzlBuilding.GetDZLHouse().GetPosition());
                        }

                        if(inventory) {
                            currentLevel = inventory.GetLevel(actualHouseDef.inventoryItemsPerLevel);
                            factor = currentLevel * 10 / 100 + 1;
                        }

                        buyPriceBuy = config.houseExtensions.pricePerLevelHouseInventory * factor;
                        if(dzlBuilding.CanBuyInventoryExtensionServer(actualHouseDef) && dzlPlayer.HasEnoughMoney(buyPriceBuy)) {
                            dzlPlayer.AddMoneyToPlayer(buyPriceBuy * -1);

                            if(!inventory) {
                                inventory = DZLDatabaseLayer.Get().GetHouseInventory(dzlBuilding.GetDZLHouse().GetOwner(), dzlBuilding.GetDZLHouse().GetPosition());
                                dzlBuilding.GetDZLHouse().EnableInventory();
                            }

                            inventory.IncreaseStorage(actualHouseDef.inventoryItemsPerLevel);

                            message = "#successfully_extend_storage";
                            GetGame().RPCSingleParam(null, DAY_Z_LIFE_OPEN_GET_BUILDING_INVENTORY_DATA_RESPONSE, new Param1<ref DZLHouseInventory>(inventory), true, sender);
                        }
                    } else {
                        if(dzlBuilding.CanBuyAlarm(extension) && dzlPlayer.HasEnoughMoney(buyPriceBuy)) {
                            buyPriceBuy = extension.price;
                            dzlPlayer.AddMoneyToPlayer(buyPriceBuy * -1);
                            dzlBuilding.SetHouseAlarm(extension);
                            message = "#successfully_buy_alarm_system";
                        }
                    }

                    GetGame().RPCSingleParam(player, DAY_Z_LIFE_BUY_EXTENSION_RESPONSE, new Param2<ref DZLBuilding, string>(dzlBuilding, message), true, sender);
                    GetGame().RPCSingleParam(player, DAY_Z_LIFE_GET_PLAYER_BUILDING_RESPONSE, new Param1<ref DZLPlayerHouse>(DZLDatabaseLayer.Get().GetPlayerHouse(sender.GetId())), true, sender);
                    dzlPlayer.GetFractionMember();
                    GetGame().RPCSingleParam(player, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(dzlPlayer), true, sender);
                }
            }
        }
    }
}
