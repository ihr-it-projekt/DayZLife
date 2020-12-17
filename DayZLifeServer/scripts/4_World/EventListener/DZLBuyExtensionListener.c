class DZLBuyExtensionListener
{
    private ref DZLPlayerInventory inventory;
    private ref DZLHouseFinder houseFinder;
	private ref DZLConfig config;

    void DZLBuyExtensionListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
        inventory = new DZLPlayerInventory;
        houseFinder = new DZLHouseFinder;
        config = DZLConfig.Get();

        houseFinder.SetConfig(config);
    }

    void ~DZLBuyExtensionListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_BUY_EXTENSION) {
			autoptr  Param3<PlayerBase, ref Building, string> paramBuyStorage;
            if (ctx.Read(paramBuyStorage)){
				
				DZLBuilding dzlBuilding = new DZLBuilding(paramBuyStorage.param2);
                DZLHouseDefinition actualHouseDef = houseFinder.GetHouseDefinitionByBuilding(paramBuyStorage.param2);

				DZLHouseExtension extension;
				array<ref DZLHouseExtension> extensions = config.GetExtensions();
				foreach(DZLHouseExtension _extension: extensions) {
					if (_extension.id == paramBuyStorage.param3) {
						extension = _extension;
						break;
					}
				}

                PlayerBase player = paramBuyStorage.param1;

				if (extension && dzlBuilding.IsOwner(player)) {
				    string message = "#error_buying_alarm_system";
				    int buyPriceBuy = 0;
				    if (extension.isStorage) {
	                    message = "#error_buying_storage";
					    buyPriceBuy =  extension.price * (actualHouseDef.storageBuyFactor * (dzlBuilding.GetStorage().Count() + 1));
					    vector posToSpawnRelavtiv = dzlBuilding.GetNextFreeStoragePosition(actualHouseDef);
					    bool canNotSpawn = posToSpawnRelavtiv == "0 0 0";

					    if (canNotSpawn) {
					        message = "#no_position_to_for_extension_found";
					    } else if(actualHouseDef.GetMaxStorage() <= dzlBuilding.GetStorage().Count()) {
					        message = "#max_storgage_is_allready_bought";
					    } else if(!inventory.PlayerHasEnoughMoney(paramBuyStorage.param1, buyPriceBuy)) {
	                        message = "#error_not_enough_money";
					    } else {
                            vector posToSpawn = paramBuyStorage.param2.ModelToWorld(posToSpawnRelavtiv);
                            bool hasSpawned = DZLSpawnHelper.SpawnContainer(posToSpawn, paramBuyStorage.param2.GetOrientation(), extension.type);

                            if (hasSpawned) {
                                inventory.AddMoneyToPlayer(player, buyPriceBuy * -1);
                                dzlBuilding.BuyStorageOnServer(new DZLStorageTypeBought(extension, posToSpawn, buyPriceBuy, posToSpawnRelavtiv));
                                message = "#successfully_buy_storage";
                            } else {
                               message = "#strorage_can_not_spawn";
                            }
                        }
				    } else {
				        if (dzlBuilding.CanBuyAlarm(extension) && inventory.PlayerHasEnoughMoney(player, buyPriceBuy) ) {
							buyPriceBuy = extension.price;
                           	inventory.AddMoneyToPlayer(player, buyPriceBuy * -1);
                           	dzlBuilding.SetHouseAlarm(extension);
                           	message = "#successfully_buy_alarm_system";
				        }
				    }

					GetGame().RPCSingleParam(paramBuyStorage.param1, DAY_Z_LIFE_BUY_EXTENSION_RESPONSE, new Param2<ref DZLBuilding, string>(dzlBuilding, message), true, sender);
	                GetGame().RPCSingleParam(paramBuyStorage.param1, DAY_Z_LIFE_GET_PLAYER_BUILDING_RESPONSE, new Param1<ref DZLPlayerHouse>(DZLDatabaseLayer.Get().GetPlayerHouse(sender.GetId())), true, sender);
				}
            }
        } else if (rpc_type == DAY_Z_LIFE_SELL_STORAGE) {
            autoptr Param3<PlayerBase, ref Building, vector> paramSellStorage;
            if (ctx.Read(paramSellStorage)){
                DZLBuilding dzlBuildingSell = new DZLBuilding(paramSellStorage.param2);
                DZLHouseDefinition actualHouseDefSell = houseFinder.GetHouseDefinitionByBuilding(paramSellStorage.param2);

                string messageSell = "#error_sell_house";

                if (actualHouseDefSell && dzlBuildingSell && dzlBuildingSell.IsOwner(paramSellStorage.param1)) {
                    DZLStorageTypeBought positionToSell = dzlBuildingSell.FindStorageByPosition(paramSellStorage.param3);
                    if (positionToSell) {
                        Container_Base itemToDestroy = houseFinder.objectFinder.GetContainerAt(positionToSell.position, positionToSell.position, positionToSell.type, paramSellStorage.param2);

                        if (itemToDestroy) {
                            inventory.AddMoneyToPlayer(paramSellStorage.param1, positionToSell.sellPrice);
                            dzlBuildingSell.SellStorageOnServer(positionToSell);

                            GetGame().ObjectDelete(itemToDestroy);
                            messageSell = "#successfully_sell_house";
                        }
                    }
                }
                GetGame().RPCSingleParam(paramSellStorage.param1, DAY_Z_LIFE_SELL_STORAGE_RESPONSE, new Param2<ref DZLBuilding, string>(dzlBuildingSell, messageSell), true, sender);
                GetGame().RPCSingleParam(paramSellStorage.param1, DAY_Z_LIFE_GET_PLAYER_BUILDING_RESPONSE, new Param1<ref DZLPlayerHouse>(DZLDatabaseLayer.Get().GetPlayerHouse(sender.GetId())), true, sender);
            }
        }
    }
}
