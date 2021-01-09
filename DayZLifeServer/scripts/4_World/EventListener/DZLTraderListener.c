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
        if (!DZLLicenceCheck.Get().HasActiveLicence(sender)) return;
        if (rpc_type == DAY_Z_LIFE_TRADE_ACTION) {
            autoptr Param4<ref array<string>,ref array<EntityAI>, ref DZLTraderPosition, PlayerBase> paramTrade;
            if (ctx.Read(paramTrade)){
                array<EntityAI> playerItems = paramTrade.param4.GetPlayerItems();
                int sum = 0;
                int countSellItems = 0;
				array<DZLTraderType> typesToBuy = new array<DZLTraderType>;
                array<EntityAI> itemsToSell = paramTrade.param2;
                array<int> itemsToSellPrice = new array<int>;
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
                        if (itemsToSell.Count() > 0) {
                            foreach(EntityAI item: itemsToSell) {
                                CarScript carsScript = CarScript.Cast(item);

                                if (carsScript && carsScript.lastDriverId != sender.GetId()) {
                                    continue;
                                }

                                if (item.GetType() == type.type) {
                                    sum -= GetPrice(item, type.sellPrice);
                                    countSellItems++;
                                    itemsToSellPrice.Insert(type.sellPrice);
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
                        DZLLogTraderTransaction(sender.GetId(), "buy", _traderType.type, _traderType.buyPrice);
                        Add(paramTrade.param4, _traderType, paramTrade.param3);
                    }

                    int index = itemsToSell.Count() - 1;
					if (index > -1) {
						EntityAI itemSell = itemsToSell.Get(index);
						int itemSellPrice = itemsToSellPrice.Get(index);
						while (itemSell) {
                            DZLLogTraderTransaction(sender.GetId(), "sell", itemSell.GetType(), itemSellPrice);
	                        GetGame().ObjectDelete(itemSell);
							
							int tmpIndex = itemsToSell.Count() - 1;

							if (tmpIndex == index) {
							    itemsToSell.Remove(index);
							}
							index = itemsToSell.Count() - 1;
							
							if (index == -1) {
								break;
							}
							itemSell = itemsToSell.Get(index);
	                    }
					}

                    dzlPlayer.AddMoneyToPlayer(sum * -1);

                    message = "#trade_was_successful";
                    GetGame().RPCSingleParam(target, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, new Param1<ref DZLPlayer>(null), true, sender);
                }

			    GetGame().RPCSingleParam(target, DAY_Z_LIFE_TRADE_ACTION_RESPONSE, new Param1<string>(message), true, sender);
            }
        }
    }


    private bool Add(PlayerBase player, DZLTraderType type, DZLTraderPosition position) {
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

			CarScript _car = CarScript.Cast(car);
			
			if (_car) {
				_car.AddOwner(player.GetIdentity());
				DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(player.GetIdentity().GetId());
			}
		}

		return !!item;
    }

    private int GetPrice(EntityAI item, int sellPrice) {
        int maxQuantity = item.GetQuantityMax();
        int quantity = item.GetQuantity();

        if (quantity == 0) {
            quantity = 1;
            maxQuantity = 1;
        }

        return Math.Round(quantity/maxQuantity * sellPrice);
    }
}
