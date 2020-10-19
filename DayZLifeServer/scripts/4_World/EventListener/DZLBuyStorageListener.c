class DZLBuyStorageListener
{
    private ref DZLPlayerInventory inventory;
    private ref DZLHouseFinder houseFinder;
	private ref DZLConfig config;

    void DZLBuyStorageListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
        inventory = new DZLPlayerInventory;
        houseFinder = new DZLHouseFinder;
        config = new DZLConfig;

        inventory.SetConfig(config.GetMoneyConfing());
        houseFinder.SetConfig(config);

        DebugMessageServerDZL("load DZLBuyStorageListener");
    }

    void ~DZLBuyStorageListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_BUY_STORAGE) {
			DebugMessageServerDZL("DAY_Z_LIFE_BUY_STORAGE");
			autoptr  Param3<PlayerBase, ref Building, ref DZLStorageType> paramBuyStorage;
            if (ctx.Read(paramBuyStorage)){
				
				DZLBuilding dzlBuilding = new DZLBuilding(paramBuyStorage.param2);
                DZLHouseDefinition actualHouseDef = houseFinder.GetHouseDefinitionByBuilding(paramBuyStorage.param2);

				DZLStorageType storageType;
				foreach(DZLStorageType _storageType: config.GetStorageTypes()) {
					if (_storageType.type == paramBuyStorage.param3.type) {
						storageType = _storageType;
						break;
					}
				}
			
				if (storageType) {
					DebugMessageServerDZL("has storage type");
	                string message = "#error_buying_storage";
					int buyPriceBuy =  storageType.price * (actualHouseDef.storageBuyFactor * (dzlBuilding.GetStorage().Count() + 1));
					vector posToSpawn = dzlBuilding.GetNextFreeStoragePosition(actualHouseDef);
					
					bool canNotSpawn = posToSpawn == "0 0 0";
	
	                if (!canNotSpawn && actualHouseDef.GetMaxStorage() > dzlBuilding.GetStorage().Count() && inventory.PlayerHasEnoughMoney(paramBuyStorage.param1, buyPriceBuy) && dzlBuilding.IsOwner(paramBuyStorage.param1)) {
	                   posToSpawn = DZLSpawnCalculator.GetPosition(paramBuyStorage.param2.GetPosition(), paramBuyStorage.param2.GetOrientation(), posToSpawn);
						
						DebugMessageServerDZL("spawn at " + posToSpawn.ToString(false));
						
						bool hasSpawned = DZLSpawnHelper.SpawnContainer(posToSpawn, paramBuyStorage.param2.GetOrientation(), storageType.type);
						
						if (hasSpawned) {
							inventory.AddMoneyToPlayer(paramBuyStorage.param1, buyPriceBuy);
							dzlBuilding.BuyStorageOnServer(new DZLStorageTypeBought(storageType, posToSpawn, buyPriceBuy));
							message = "#successfully_buy_storage";
						}

					}
					
					GetGame().RPCSingleParam(paramBuyStorage.param1, DAY_Z_LIFE_BUY_STORAGE_RESPONSE, new Param2<ref DZLBuilding, string>(dzlBuilding, message), true, sender);
	                GetGame().RPCSingleParam(paramBuyStorage.param1, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE, new Param1<ref DZLPlayerHouse>(new DZLPlayerHouse(paramBuyStorage.param1)), true, sender);
				} else {
					DebugMessageServerDZL("has NO storage type");
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
                            DebugMessageServerDZL("has object to destroy");
                            inventory.AddMoneyToPlayer(paramSellStorage.param1, positionToSell.sellPrice);
                            dzlBuildingSell.SellStorageOnServer(positionToSell);

                            GetGame().ObjectDelete(itemToDestroy);
                            messageSell = "#successfully_sell_house";
                        }
                    }
                }
                GetGame().RPCSingleParam(paramSellStorage.param1, DAY_Z_LIFE_SELL_STORAGE_RESPONSE, new Param2<ref DZLBuilding, string>(dzlBuildingSell, messageSell), true, sender);
                GetGame().RPCSingleParam(paramSellStorage.param1, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE, new Param1<ref DZLPlayerHouse>(new DZLPlayerHouse(paramSellStorage.param1)), true, sender);
            }
        }
    }
}