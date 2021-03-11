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
        if (rpc_type == DAY_Z_LIFE_EVENT_GET_CAR_DATA_FROM_STORAGE) {
			GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_GET_CAR_DATA_FROM_STORAGE_RESPONSE, new Param1<ref DZLCarStorage>(DZLDatabaseLayer.Get().GetPlayerCarStorage(sender.GetId())), true, sender);
        } else if (rpc_type == DAY_Z_LIFE_EVENT_STORE_CAR) {
            autoptr Param1<vector> paramStoreCar;
            CarScript car = CarScript.Cast(target);
			
			if (car && car.IsRuined()) {
				DZLSendMessage(sender, "#car_can_not_store_is_ruined");
			} else if (ctx.Read(paramStoreCar) && paramStoreCar.param1 && car){
				DZLStoragePosition storagePosition = config.GetStorageByPosition(paramStoreCar.param1);
				
				if (!storagePosition) return;

				CargoBase cargo = car.GetInventory().GetCargo();
                if (!config.canStoreCarsWithGoods && cargo && cargo.GetItemCount() > 0) {
                    DZLSendMessage(sender, "#car_is_not_empty");
                    return;
                }
				
                DZLCarStorage storageIn = DZLDatabaseLayer.Get().GetPlayerCarStorage(sender.GetId());
                storageIn.Add(car, storagePosition.position, config.canStoreCarsWithGoods, false);
				
				DZLInsuranceManager.Get().RemoveCar(car);

                DZLLogStore(sender.GetId(), "store in", car.GetType(), storagePosition.position);
				GetGame().ObjectDelete(car);
				DZLSendMessage(sender, "#car_was_parked");
				GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_GET_CAR_DATA_FROM_STORAGE_RESPONSE, new Param1<ref DZLCarStorage>(storageIn), true, sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CAR_FROM_STORAGE) {
            autoptr Param2<string, bool> paramGetCar;
            PlayerBase player = PlayerBase.Cast(target);
            if (ctx.Read(paramGetCar) && player){
                string itemId = paramGetCar.param1;
                bool withInsurance = paramGetCar.param2;
                DZLPlayer dzlPlayer = player.GetDZLPlayer();

                if (withInsurance && !dzlPlayer.HasEnoughMoneBank(config.carInsurancePrice)) {
                    DZLSendMessage(sender, "#error_not_enough_money");
                    return;
                }

                DZLCarStorage storage = DZLDatabaseLayer.Get().GetPlayerCarStorage(sender.GetId());
				DZLStoragePosition storagePositionCar = config.GetStorageByPosition(player.GetPosition());
				
                DZLCarStoreItem storedCar = storage.GetById(itemId);

                if (!storedCar) return;

                if (!config.canGetCarsFromEveryGarage && storedCar.positionOfStore != storagePositionCar.position) return;

				CarScript carSpawned = SpawnCar(player, storedCar, storagePositionCar, withInsurance);

                if (carSpawned) {
                    storage.RemoveItem(storedCar);
                    GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_GET_CAR_DATA_FROM_STORAGE_RESPONSE, new Param1<ref DZLCarStorage>(storage), true, sender);
                    DZLLogStore(sender.GetId(), "store out insurance: " + withInsurance.ToString(), carSpawned.GetType(), storagePositionCar.position);

                    if (withInsurance) {
                        dzlPlayer.AddMoneyToPlayerBank(config.carInsurancePrice * -1);
                        DZLInsuranceManager.Get().AddCar(carSpawned, null);
                        GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, sender);
                    }
                }
            }
        }

    }
	
    private CarScript SpawnCar(PlayerBase player, DZLCarStoreItem itemInStock, DZLStoragePosition storagePositionCar, bool enableInsurance) {
		EntityAI item;
		CarScript car;
        item = player.SpawnEntityOnGroundPos(itemInStock.type, storagePositionCar.spawnPositionOfVehicles);

        if (!item) {
            return null;
        }

        car = CarScript.Cast(item);

        if (car) {
			array<ref DZLStoreItem> attached = itemInStock.attached;
			bool spawnOnGround = false;
			foreach(DZLStoreItem attach: attached) {
				if (DZLSpawnHelper.Add(car, attach) && !spawnOnGround) {
				    spawnOnGround = true;
				}
			}

			if (spawnOnGround) {
			    DZLSendMessage(player.GetIdentity(), "#car_was_parked_out_some_items_can_not_placed_in_car");
			} else {
			    DZLSendMessage(player.GetIdentity(), "#car_was_parked_out");
			}

			if (enableInsurance) {
			    car.EnableInsurance(storagePositionCar.position);
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
}
