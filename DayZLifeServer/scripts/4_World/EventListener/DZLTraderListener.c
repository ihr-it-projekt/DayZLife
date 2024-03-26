class DZLTraderListener: DZLBaseEventListener {

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.TRADE_ACTION) {
            Param3<ref array<string>, ref array<EntityAI>, ref DZLTraderPosition> paramTrade;
            if(!ctx.Read(paramTrade)) return;

            DZLTradeObject tradeObject = new DZLTradeObject(PlayerBase.Cast(target), paramTrade.param2, paramTrade.param1, paramTrade.param3);

            tradeObject.CheckCategories();
            if(!tradeObject.CanTrade()) return;

            tradeObject.Trade();
            tradeObject.SaveStorage();
            tradeObject.LogTrades();
            tradeObject.SendTraderResponse();
        } else if(rpc_type == DZL_RPC.EVENT_GET_CONFIG_TRADER_STORAGE) {
            GetGame().RPCSingleParam(target, DZL_RPC.EVENT_GET_CONFIG_TRADER_STORAGE_RESPONSE, new Param1<ref array<ref DZLTraderTypeStorage>>(DZLDatabaseLayer.Get().GetTraderStorage().GetStorageItems()), true, sender);
        }
    }

    private bool Add(PlayerBase player, DZLTraderType type, DZLTraderPosition position) {
        EntityAI item;
        InventoryLocation inventoryLocation = new InventoryLocation;

        if(!type.usePlayerAsSpawnPoint) {
            item = player.SpawnEntityOnGroundPos(type.type, position.spawnPositionOfVehicles);
            item.SetOrientation(position.spawnOrientationOfVehicles);

        } else {
            if(player.GetInventory().FindFirstFreeLocationForNewEntity(type.type, FindInventoryLocationType.ANY, inventoryLocation)) {
                item = player.GetHumanInventory().CreateInInventory(type.type);
            } else if(!player.GetHumanInventory().GetEntityInHands()) {
                item = player.GetHumanInventory().CreateInHands(type.type);
            }

            if(!item) {
                item = player.SpawnEntityOnGroundPos(type.type, player.GetPosition());
            }

            if(DZLTraderHelper.IsStackable(item)) {
                ItemBase itemBase = ItemBase.Cast(item);
                itemBase.SetQuantity(1);
            }
        }

        if(item && item.GetInventory()) {
            foreach(string attachment: type.attachments) {
                item.GetInventory().CreateAttachment(attachment);
            }
        }

        if(item && type.isCar) {
            Car car = Car.Cast(item);

            car.Fill(CarFluid.FUEL, car.GetFluidCapacity(CarFluid.FUEL));
            car.Fill(CarFluid.OIL, car.GetFluidCapacity(CarFluid.OIL));
            car.Fill(CarFluid.BRAKE, car.GetFluidCapacity(CarFluid.BRAKE));
            car.Fill(CarFluid.COOLANT, car.GetFluidCapacity(CarFluid.COOLANT));

            car.Fill(CarFluid.USER1, car.GetFluidCapacity(CarFluid.USER1));
            car.Fill(CarFluid.USER2, car.GetFluidCapacity(CarFluid.USER2));
            car.Fill(CarFluid.USER3, car.GetFluidCapacity(CarFluid.USER3));
            car.Fill(CarFluid.USER4, car.GetFluidCapacity(CarFluid.USER4));

            CarScript _car = CarScript.Cast(car);
            if(_car) {
                _car.OwnCar(player.GetIdentity(), "", "");
            }
        }

        return !!item;
    }
}
