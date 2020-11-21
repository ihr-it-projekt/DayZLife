class DZLBuyHouseListener
{
    private ref DZLPlayerInventory inventory;
    private ref DZLHouseFinder houseFinder;

    void DZLBuyHouseListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
        inventory = new DZLPlayerInventory;
        houseFinder = new DZLHouseFinder;
        DZLConfig config = new DZLConfig;

        houseFinder.SetConfig(config);
    }

    void ~DZLBuyHouseListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_OPEN_GET_BUILDING_DATA) {
            autoptr Param2<PlayerBase, ref Building> paramGetBuildingProperties;
            if (ctx.Read(paramGetBuildingProperties)){
                GetGame().RPCSingleParam(paramGetBuildingProperties.param1, DAY_Z_LIFE_OPEN_GET_BUILDING_DATA_RESPONSE, new Param1<ref DZLBuilding>(new DZLBuilding(paramGetBuildingProperties.param2)), true, sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_OPEN_BUY_BUILDING) {
            autoptr Param2<PlayerBase, ref Building> paramBuyHouse;
            if (ctx.Read(paramBuyHouse)){
				DZLBuilding dzlBuilding = new DZLBuilding(paramBuyHouse.param2);
                DZLHouseDefinition actualHouseDef = houseFinder.GetHouseDefinitionByBuilding(paramBuyHouse.param2);
				DZLPlayer dzlPlayer = new DZLPlayer(paramBuyHouse.param1.GetIdentity().GetId());

                string message = "#error_buying_house";

                if (actualHouseDef && dzlBuilding && !dzlBuilding.HasOwner() && dzlPlayer.HasEnoughMoney(actualHouseDef.buyPrice)) {
                    inventory.AddMoneyToPlayer(paramBuyHouse.param1, actualHouseDef.buyPrice * -1);
                    dzlBuilding.BuyOnServer(paramBuyHouse.param1);

                    message = "#successfully_buy_house";
                }
                GetGame().RPCSingleParam(paramBuyHouse.param1, DAY_Z_LIFE_OPEN_BUY_BUILDING_RESPONSE, new Param2<ref DZLBuilding, string>(dzlBuilding, message), true, sender);
                GetGame().RPCSingleParam(paramBuyHouse.param1, DAY_Z_LIFE_GET_PLAYER_BUILDING_RESPONSE, new Param1<ref DZLPlayerHouse>(new DZLPlayerHouse(sender)), true, sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_OPEN_SELL_BUILDING) {
            autoptr Param2<PlayerBase, ref Building> paramSellHouse;
            if (ctx.Read(paramSellHouse)){
				DZLBuilding dzlBuildingSell = new DZLBuilding(paramSellHouse.param2);
                DZLHouseDefinition actualHouseDefSell = houseFinder.GetHouseDefinitionByBuilding(paramSellHouse.param2);
                string messageSell = "#error_sell_house";

                if (actualHouseDefSell && dzlBuildingSell && dzlBuildingSell.IsOwner(paramSellHouse.param1)) {
                    float sellPrice = actualHouseDefSell.sellPrice;

                    array<ref DZLStorageTypeBought> storages = dzlBuildingSell.GetStorage();
                    foreach(DZLStorageTypeBought storage: storages) {
                        if (!storage) continue;
                        Container_Base itemToDestroy = houseFinder.objectFinder.GetContainerAt(storage.position, storage.position, storage.type, paramSellHouse.param2);

                        if (!itemToDestroy) continue;
                        sellPrice += storage.sellPrice;
                        GetGame().ObjectDelete(itemToDestroy);
                    }

                    dzlBuildingSell.GetStorage().Clear();

                    inventory.AddMoneyToPlayer(paramSellHouse.param1, sellPrice);
                    dzlBuildingSell.SellOnServer(paramSellHouse.param1);

                    messageSell = "#successfully_sell_house";
                }
                GetGame().RPCSingleParam(paramSellHouse.param1, DAY_Z_LIFE_OPEN_SELL_BUILDING_RESPONSE, new Param2<ref DZLBuilding, string>(dzlBuildingSell, messageSell), true, sender);
                GetGame().RPCSingleParam(paramSellHouse.param1, DAY_Z_LIFE_GET_PLAYER_BUILDING_RESPONSE, new Param1<ref DZLPlayerHouse>(new DZLPlayerHouse(sender)), true, sender);
            }
        }
    }
}