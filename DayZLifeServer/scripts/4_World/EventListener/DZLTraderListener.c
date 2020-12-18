class DZLTraderListener
{
    ref DZLTraderConfig config;

    void DZLTraderListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
        config = DZLConfig.Get().traderConfig;
    }

    void ~DZLTraderListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_TRADE_ACTION) {
            autoptr Param4<ref array<string>,ref array<EntityAI>, ref DZLTraderPosition, PlayerBase> paramTrade;
            if (ctx.Read(paramTrade)){
                array<EntityAI> playerItems = paramTrade.param4.GetPlayerItems();
                int sum = 0;
                int countSellItems = 0;
				array<DZLTraderType> typesToBuy = new array<DZLTraderType>;
                array<EntityAI> itemsToSell = paramTrade.param2;
                array<string> itemsToBuyParam = paramTrade.param1;

                foreach(string categoryName: paramTrade.param3.categoryNames) {
                    DZLTraderCategory category = config.categories.GetCatByName(categoryName);

                    if (!category) continue;
					
                    foreach(DZLTraderType type: category.items) {
                        if (itemsToBuyParam.Count() > 0) {
                            foreach(string traderType: itemsToBuyParam) {
                                if (traderType == type.id) {
                                    typesToBuy.Insert(type);
                                    sum += type.buyPrice;
                                }
                            }
                        }
                        if (paramTrade.param2.Count() > 0) {
                            foreach(EntityAI item: itemsToSell) {
                                if (item.GetType() == type.type) {
                                    sum -= type.sellPrice;
                                    countSellItems++;
                                }
                            }
                        }
                    }
                }

                DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(sender.GetId());
                string message = "#error_not_enough_money";

                if (typesToBuy.Count() == 0 &&  countSellItems == 0) {
                    message = "#you_have_to_trade_minimum_one_item";
                } else if (typesToBuy.Count() != itemsToBuyParam.Count() && countSellItems != itemsToSell.Count()) {
                    message = "#not_all_items_found_that_you_want_to_trade";
                } else if (dzlPlayer.HasEnoughMoney(sum)) {
                    foreach(DZLTraderType _traderType: typesToBuy) {
                        Add(paramTrade.param4, _traderType, paramTrade.param3);
                    }

                    int index = itemsToSell.Count() - 1;
					if (index > -1) {
						item = itemsToSell.Get(index);
						while (item) {
	                        GetGame().ObjectDelete(item);
							
							int tmpIndex = itemsToSell.Count() - 1;

							if (tmpIndex == index) {
							    itemsToSell.Remove(index);
							}
							index = itemsToSell.Count() - 1;
							
							if (index == -1) {
								break;
							}
							item = itemsToSell.Get(index);
	                    }
					}

                    dzlPlayer.AddMoneyToPlayer(sum * -1);

                    message = "#trade_was_successful";
                    GetGame().RPCSingleParam(target, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(dzlPlayer), true, sender);
                }

			    GetGame().RPCSingleParam(target, DAY_Z_LIFE_TRADE_ACTION_RESPONSE, new Param1<string>(message), true, sender);
            }
        }
    }


    private void Add(PlayerBase player, DZLTraderType type, DZLTraderPosition position) {
        EntityAI item;
        InventoryLocation inventoryLocation = new InventoryLocation;
		
		if (!type.usePlayerAsSpawnPoint) {
			item = player.SpawnEntityOnGroundPos(type.type, position.spawnPositionOfVehicles);
			item.SetOrientation(position.spawnOrientationOfVehicles);
			
		} else {
			if (player.GetInventory().FindFirstFreeLocationForNewEntity(type.type, FindInventoryLocationType.ANY, inventoryLocation)) {
	            item = player.GetHumanInventory().CreateInInventory(type.type);
	        } else if (!player.GetHumanInventory().GetEntityInHands()) {
	            item = player.GetHumanInventory().CreateInHands(type.type);
	        }
	
	        if (!item) {
	            item = player.SpawnEntityOnGroundPos(type.type, player.GetPosition());
	        }
		}

		if (item) {
			
			foreach(string attachment: type.attachments) {
				if (item.GetInventory()) {
					item.GetInventory().CreateAttachment(attachment);
				}
			}
		}

		if (item && type.isCar) {
			Car car = Car.Cast(item);

		    car.Fill(CarFluid.FUEL, car.GetFluidCapacity(CarFluid.FUEL));
            car.Fill(CarFluid.OIL, car.GetFluidCapacity(CarFluid.OIL));
            car.Fill(CarFluid.BRAKE, car.GetFluidCapacity(CarFluid.BRAKE));
            car.Fill(CarFluid.COOLANT, car.GetFluidCapacity(CarFluid.COOLANT));

            car.Fill(CarFluid.USER1, car.GetFluidCapacity(CarFluid.USER1));
            car.Fill(CarFluid.USER2, car.GetFluidCapacity(CarFluid.USER2));
            car.Fill(CarFluid.USER3, car.GetFluidCapacity(CarFluid.USER3));
            car.Fill(CarFluid.USER4, car.GetFluidCapacity(CarFluid.USER4));
		}
    }
}
