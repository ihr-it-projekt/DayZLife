class DZLStorageListener
{
    ref DZLCarConfig config;

    void DZLStorageListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
        config = DZLConfig.Get().carConfig;
    }

    void ~DZLStorageListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (!DZLLicenceCheck.Get().HasActiveLicence(sender)) return;
        if (rpc_type == DAY_Z_LIFE_EVENT_GET_CAR_DATA_FROM_STORAGE) {
			GetGame().RPCSingleParam(target, DAY_Z_LIFE_EVENT_GET_CAR_DATA_FROM_STORAGE_RESPONSE, new Param1<ref DZLCarStorage>(DZLDatabaseLayer.Get().GetPlayerCarStorage(sender.GetId())), true, sender);
        } else if (rpc_type == DAY_Z_LIFE_EVENT_STORE_CAR) {
            autoptr Param2<CarScript, PlayerBase> paramStoreCar;
            if (ctx.Read(paramStoreCar) && paramStoreCar.param1){
				CarScript car = paramStoreCar.param1;
				DZLStoragePosition storagePosition = config.GetStorageByPosition(paramStoreCar.param2);
				
				if (!storagePosition) return;

				CargoBase cargo = car.GetInventory().GetCargo();
                if (!config.canStoreCarsWithGoods && cargo && cargo.GetItemCount() > 0) {
                    DZLSendMessage(sender, "#car_is_not_empty");
                    return;
                }
				
                DZLCarStorage storageIn = DZLDatabaseLayer.Get().GetPlayerCarStorage(sender.GetId());
                storageIn.Add(car, storagePosition.position);
                DZLLogStore(sender.GetId(), "store in", car.GetType(), storagePosition.position);
				GetGame().ObjectDelete(car);
				DZLSendMessage(sender, "#car_was_parked");
				GetGame().RPCSingleParam(target, DAY_Z_LIFE_EVENT_GET_CAR_DATA_FROM_STORAGE_RESPONSE, new Param1<ref DZLCarStorage>(storageIn), true, sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CAR_FROM_STORAGE) {
            autoptr Param2<PlayerBase, string> paramGetCar;
            if (ctx.Read(paramGetCar) && paramGetCar.param1){
                PlayerBase player = paramGetCar.param1;
                string itemId = paramGetCar.param2;

                DZLCarStorage storage = DZLDatabaseLayer.Get().GetPlayerCarStorage(sender.GetId());
				DZLStoragePosition storagePositionCar = config.GetStorageByPosition(player);
				
                DZLCarStoreItem storedCar = storage.GetById(itemId);

                if (!storedCar) return;

                if (!config.canGetCarsFromEveryGarage && storedCar.positionOfStore != storagePositionCar.position) return;

				CarScript carSpawned = SpawnCar(player, storedCar,storagePositionCar);

                if (carSpawned) {
                    storage.RemoveItem(storedCar);
                    GetGame().RPCSingleParam(target, DAY_Z_LIFE_EVENT_GET_CAR_DATA_FROM_STORAGE_RESPONSE, new Param1<ref DZLCarStorage>(storage), true, sender);
                    DZLLogStore(sender.GetId(), "store out", carSpawned.GetType(), storagePosition.position);
                    DZLSendMessage(sender, "#car_was_parked_out");
                }
            }
        }

    }
	
    private CarScript SpawnCar(PlayerBase player, DZLCarStoreItem itemInStock, DZLStoragePosition storagePositionCar) {
		EntityAI item;
		CarScript car;
        item = player.SpawnEntityOnGroundPos(itemInStock.type, storagePositionCar.spawnPositionOfVehicles);

        if (!item) {
            return null;
        }

        car = CarScript.Cast(item);

        if (car) {
			array<ref DZLStoreItem> attached = itemInStock.attached;
			
			foreach(DZLStoreItem attach: attached) {
				Add(car, attach);
			}
			
			car.AddOwner(player.GetIdentity());
			car.UpdatePlayerAccess(itemInStock.playerAccess);
			car.SetOrientation(storagePositionCar.spawnOrientationOfVehicles);

			FillFluid(car, CarFluid.FUEL, itemInStock.fuel);
            FillFluid(car, CarFluid.OIL, itemInStock.oil);
            FillFluid(car, CarFluid.BRAKE, itemInStock.brake);
            FillFluid(car, CarFluid.COOLANT, itemInStock.coolant);
            FillFluid(car, CarFluid.USER1, itemInStock.user1);
            FillFluid(car, CarFluid.USER2, itemInStock.user2);
            FillFluid(car, CarFluid.USER3, itemInStock.user3);
            FillFluid(car, CarFluid.USER4, itemInStock.user4);
        }

        return car;
    }

    private void FillFluid(CarScript car, int type, float inPercent) {
		if (inPercent > 0) {
			car.Fill(type, car.GetFluidCapacity(type) * inPercent);
		}
	}
	
	 private EntityAI Add(EntityAI parent, DZLStoreItem itemInStock, ref InventoryLocation inventoryLocation = null) {
        EntityAI item;

        if (!inventoryLocation) {
            inventoryLocation = new InventoryLocation;
        }

        if (parent.GetInventory().FindFirstFreeLocationForNewEntity(itemInStock.type, FindInventoryLocationType.ANY, inventoryLocation)) {
            item = parent.GetInventory().CreateInInventory(itemInStock.type);
        }

        if(!item) {
            item = parent.GetInventory().CreateAttachment(itemInStock.type);
        }

        if(!item) {
			item = parent.GetInventory().CreateEntityInCargo(itemInStock.type);
        }

		item.SetHealth(itemInStock.health);

        ItemBase castItem;
        if(item.IsMagazine()) {
            Magazine mag = Magazine.Cast(item);

            if (!mag) {
                return item;
            }
            mag.ServerSetAmmoCount(itemInStock.GetQuantity());
        } else if(item.IsAmmoPile()) {
            Ammunition_Base ammo = Ammunition_Base.Cast(item);

            if (!ammo) {
                return item;
            }
            ammo.ServerSetAmmoCount(itemInStock.GetQuantity());
        } else if (ItemBase.CastTo(castItem, item)) {
            castItem.SetQuantity(itemInStock.GetQuantity(), true, true);
        }

        if(itemInStock.attached.Count() > 0) {
            foreach(DZLStoreItem itemAttached: itemInStock.attached) {
                this.Add(item, itemAttached, inventoryLocation);
            }
        }
		
		return item;
    }
}
