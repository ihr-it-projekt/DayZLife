class DZLTraderListener: DZLBaseEventListener {

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.TRADE_ACTION) {
            autoptr Param3<ref array<string>, ref array<EntityAI>, ref DZLTraderPosition> paramTrade;
            if(ctx.Read(paramTrade)) {
                array<EntityAI> playerItems = PlayerBase.Cast(target).GetPlayerItems();
                int sum = 0;
                int taxSum = 0;
                int countSellItems = 0;
                array<DZLTraderType> typesToBuy = new array<DZLTraderType>;
                array<EntityAI> itemsToSell = paramTrade.param2;
                array<int> itemsToSellPrice = new array<int>;
                array<string> itemsToBuyParam = paramTrade.param1;
                DZLTraderConfig config = DZLConfig.Get().traderConfig;
                DZLBankingConfig bankConfig = DZLConfig.Get().bankConfig;
                foreach(string categoryName: paramTrade.param3.categoryNames) {
                    DZLTraderCategory category = config.categories.GetCatByName(categoryName);
                    if(!category) continue;

                    foreach(DZLTraderType type: category.items) {
                        if(itemsToBuyParam.Count() <= 0) continue;
                        DZLTraderTypeStorage storage = DZLDatabaseLayer.Get().GetTraderStorage().GetCurrentStorageByName(type.type);
                        foreach(string traderType: itemsToBuyParam) {
                            if(traderType != type.GetId()) continue;
                            if(storage) {
                                if(storage.IsStorageBelowZero()) {
                                    DZLSendMessage(sender, "#you_buy_too_much");
                                    break;
                                }
                                storage.StorageDown();
                                storage.Save();
                            }

                            typesToBuy.Insert(type);
                            sum += type.CalculateDynamicBuyPrice(storage);
                        }
                        if(itemsToSell.Count() <= 0) continue;
                        foreach(EntityAI item: itemsToSell) {
                            CarScript carsScript = CarScript.Cast(item);

                            if(carsScript && carsScript.ownerId != sender.GetId()) continue;
                            if(!item || !type) continue;
                            if(item.GetType() != type.type) continue;

                            if(storage) {
                                if(storage.IsStorageOverFilled()) {
                                    DZLSendMessage(sender, "#you_sell_too_much");
                                    break;
                                }
                                storage.StorageUp(DZLTraderHelper.GetQuantity(item));
                                storage.Save();
                            }
                            itemsToSellPrice.Insert(type.sellPrice);
                            float itemPrice = type.CalculateDynamicSellPrice(storage, item);
                            itemPrice = DZLTraderHelper.GetQuantityPrice(itemPrice, item);

                            float itemTax = itemPrice / 100 * bankConfig.sellTradingTax;
                            countSellItems++;
                            sum -= Math.Round(itemPrice - itemTax);
                            taxSum += Math.Round(itemTax);
                        }
                    }
                }

                PlayerBase player = PlayerBase.Cast(target);
                DZLPlayer dzlPlayer = player.GetDZLPlayer();
                string message = "#error_not_enough_money";

                if(typesToBuy.Count() == 0 && countSellItems == 0) {
                    message = "#you_have_to_trade_minimum_one_item";
                } else if(typesToBuy.Count() != itemsToBuyParam.Count() && countSellItems != itemsToSell.Count()) {
                    message = "#not_all_items_found_that_you_want_to_trade";
                } else if(dzlPlayer.HasEnoughMoney(sum)) {
                    foreach(DZLTraderType _traderType: typesToBuy) {
                        DZLLogTraderTransaction(sender.GetId(), "buy", _traderType.type, _traderType.buyPrice);
                        Add(player, _traderType, paramTrade.param3);
                    }

                    int index = itemsToSell.Count() - 1;
                    if(index > -1) {
                        EntityAI itemSell = itemsToSell.Get(index);
                        int itemSellPrice = itemsToSellPrice.Get(index);
                        while(itemSell) {
                            DZLLogTraderTransaction(sender.GetId(), "sell", itemSell.GetType(), itemSellPrice);
                            GetGame().ObjectDelete(itemSell);

                            int tmpIndex = itemsToSell.Count() - 1;

                            if(tmpIndex == index) itemsToSell.Remove(index);

                            CarScript car = CarScript.Cast(itemSell);
                            if(car) DZLInsuranceManager.Get().RemoveCar(car);

                            index = itemsToSell.Count() - 1;
                            if(index == -1) break;

                            itemSell = itemsToSell.Get(index);
                        }
                    }

                    dzlPlayer.AddMoneyToPlayer(sum * -1);
                    DZLBank bank = DZLDatabaseLayer.Get().GetBank();
                    bank.AddTax(taxSum);

                    message = "#trade_was_successful";
                    GetGame().RPCSingleParam(target, DZL_RPC.PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(bank), true);
                    GetGame().RPCSingleParam(null, DZL_RPC.EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, sender);
                }

                GetGame().RPCSingleParam(target, DZL_RPC.TRADE_ACTION_RESPONSE, new Param1<string>(message), true, sender);
            }
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
