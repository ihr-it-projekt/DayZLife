class DZLBuyExtensionListener
{
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
        if (rpc_type == DAY_Z_LIFE_BUY_EXTENSION) {
			autoptr  Param2<Building, string> paramBuyStorage;
            if (ctx.Read(paramBuyStorage)){
				PlayerBase player = PlayerBase.Cast(target);
				DZLPlayer dzlPlayer = player.GetDZLPlayer();
				DZLBuilding dzlBuilding = new DZLBuilding(paramBuyStorage.param1);
                DZLHouseDefinition actualHouseDef = houseFinder.GetHouseDefinitionByBuilding(paramBuyStorage.param1);

				DZLHouseExtension extension;
				array<ref DZLHouseExtension> extensions = config.GetExtensions();
				foreach(DZLHouseExtension _extension: extensions) {
					if (_extension.GetId() == paramBuyStorage.param2) {
						extension = _extension;
						break;
					}
				}

				if (extension && dzlBuilding.IsOwner(player)) {
				    string message = "#error_buying_alarm_system";
				    int buyPriceBuy = 0;
				    if (extension.isStorage) {
	                    message = "#error_buying_storage";
					    buyPriceBuy =  extension.price * (actualHouseDef.storageBuyFactor * (dzlBuilding.GetStorage().Count() + 1));
					    vector posToSpawnRelative = dzlBuilding.GetNextFreeStoragePosition(actualHouseDef);
					    bool canNotSpawn = posToSpawnRelative == "0 0 0";

					    if (canNotSpawn) {
					        message = "#no_position_to_for_extension_found";
					    } else if(actualHouseDef.GetMaxStorage() <= dzlBuilding.GetStorage().Count()) {
					        message = "#max_storgage_is_allready_bought";
					    } else if(!dzlPlayer.HasEnoughMoney(buyPriceBuy)) {
	                        message = "#error_not_enough_money";
					    } else {
                            vector posToSpawn = paramBuyStorage.param1.ModelToWorld(posToSpawnRelative);
                            bool hasSpawned = DZLSpawnHelper.SpawnContainer(posToSpawn, paramBuyStorage.param1.GetOrientation(), extension.type);

                            if (hasSpawned) {
                                dzlPlayer.AddMoneyToPlayer(buyPriceBuy * -1);
                                dzlBuilding.BuyStorageOnServer(new DZLStorageTypeBought(extension, posToSpawn, buyPriceBuy, posToSpawnRelative));
                                message = "#successfully_buy_storage";
                            } else {
                               message = "#strorage_can_not_spawn";
                            }
                        }
				    } else if (extension.isHouseInventory) {
				        DZLHouseInventory inventory;
						int currentLevel = 0;
						float factor = 1.0;
				        if (dzlBuilding.HasInventory()) {
				            inventory = DZLDatabaseLayer.Get().GetHouseInventory(dzlBuilding.GetDZLHouse().GetOwner(), dzlBuilding.GetDZLHouse().GetPosition());
						}
					
				        if (inventory) {
                            currentLevel = inventory.GetLevel(config.houseExtensions.inventoryItemsPerLevel);
                            factor = currentLevel * 10 / 100 + 1;
                        }

				        buyPriceBuy = config.houseExtensions.pricePerLevelHouseInventory * factor;
				        if (dzlBuilding.CanBuyInventoryExtensionServer(config.houseExtensions) && dzlPlayer.HasEnoughMoney(buyPriceBuy)) {
                           	dzlPlayer.AddMoneyToPlayer(buyPriceBuy * -1);

                           	if (!inventory) {
                           	    inventory = DZLDatabaseLayer.Get().GetHouseInventory(dzlBuilding.GetDZLHouse().GetOwner(), dzlBuilding.GetDZLHouse().GetPosition());
                           	    dzlBuilding.GetDZLHouse().EnableInventory();
                           	}

                           	inventory.IncreaseStorage(config.houseExtensions.inventoryItemsPerLevel);

                           	message = "#successfully_extend_storage";
                           	GetGame().RPCSingleParam(null, DAY_Z_LIFE_OPEN_GET_BUILDING_INVENTORY_DATA_RESPONSE, new Param1<ref DZLHouseInventory>(inventory), true, sender);
				        }
				    } else {
				        if (dzlBuilding.CanBuyAlarm(extension) && dzlPlayer.HasEnoughMoney(buyPriceBuy) ) {
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
        } else if (rpc_type == DAY_Z_LIFE_SELL_STORAGE) {
            autoptr Param2<Building, vector> paramSellStorage;
            if (ctx.Read(paramSellStorage)){
                PlayerBase playerSellStorage = PlayerBase.Cast(target);
				DZLPlayer dzlPlayerSellStorage = playerSellStorage.GetDZLPlayer();
                DZLBuilding dzlBuildingSell = new DZLBuilding(paramSellStorage.param1);
                DZLHouseDefinition actualHouseDefSell = houseFinder.GetHouseDefinitionByBuilding(paramSellStorage.param1);

                string messageSell = "#error_sell_house";

                if (actualHouseDefSell && dzlBuildingSell && dzlBuildingSell.IsOwner(playerSellStorage)) {
                    DZLStorageTypeBought positionToSell = dzlBuildingSell.FindStorageByPosition(paramSellStorage.param2);
                    if (positionToSell) {
                        houseFinder.objectFinder.DeleteContainerAt(positionToSell.position, positionToSell.position, positionToSell.type, paramSellStorage.param1);

                        dzlPlayerSellStorage.AddMoneyToPlayer(positionToSell.sellPrice);
                        dzlBuildingSell.SellStorageOnServer(positionToSell);

                        messageSell = "#successfully_sell_house";
                       
                    }
                }
                GetGame().RPCSingleParam(playerSellStorage, DAY_Z_LIFE_SELL_STORAGE_RESPONSE, new Param2<ref DZLBuilding, string>(dzlBuildingSell, messageSell), true, sender);
                GetGame().RPCSingleParam(playerSellStorage, DAY_Z_LIFE_GET_PLAYER_BUILDING_RESPONSE, new Param1<ref DZLPlayerHouse>(DZLDatabaseLayer.Get().GetPlayerHouse(sender.GetId())), true, sender);
                dzlPlayerSellStorage.GetFractionMember();
                GetGame().RPCSingleParam(playerSellStorage, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(dzlPlayerSellStorage), true, sender);
            }
        }
    }
}
