class DZLBuyHouseListener
{
    private ref DZLHouseFinder houseFinder;

    void DZLBuyHouseListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
        houseFinder = new DZLHouseFinder;
        DZLConfig config = DZLConfig.Get();

        houseFinder.SetConfig(config);
    }

    void ~DZLBuyHouseListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_OPEN_GET_BUILDING_DATA) {
            autoptr Param1<Building> paramGetBuildingProperties;
            if (ctx.Read(paramGetBuildingProperties)){
                GetGame().RPCSingleParam(PlayerBase.Cast(target), DAY_Z_LIFE_OPEN_GET_BUILDING_DATA_RESPONSE, new Param1<ref DZLBuilding>(new DZLBuilding(paramGetBuildingProperties.param1)), true, sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_OPEN_BUY_BUILDING) {
            autoptr Param1<Building> paramBuyHouse;
            if (ctx.Read(paramBuyHouse)){
				DZLBuilding dzlBuilding = new DZLBuilding(paramBuyHouse.param1);
                DZLHouseDefinition actualHouseDef = houseFinder.GetHouseDefinitionByBuilding(paramBuyHouse.param1);
                PlayerBase playerOpenBuy = PlayerBase.Cast(target);
				DZLPlayer dzlPlayer = playerOpenBuy.GetDZLPlayer();;

                string message = "#error_buying_house";

                if (actualHouseDef && dzlBuilding && !dzlBuilding.HasOwner() && dzlPlayer.HasEnoughMoney(actualHouseDef.buyPrice)) {
                    dzlPlayer.AddMoneyToPlayer(actualHouseDef.buyPrice * -1);
                    dzlBuilding.BuyOnServer(playerOpenBuy);

                    message = "#successfully_buy_house";
                    DZLLogHouseTrade(sender.GetId(), "buy house", actualHouseDef.buyPrice, dzlBuilding.GetDZLHouse().GetPosition());
                }
                GetGame().RPCSingleParam(playerOpenBuy, DAY_Z_LIFE_OPEN_BUY_BUILDING_RESPONSE, new Param2<ref DZLBuilding, string>(dzlBuilding, message), true, sender);
                GetGame().RPCSingleParam(playerOpenBuy, DAY_Z_LIFE_GET_PLAYER_BUILDING_RESPONSE, new Param1<ref DZLPlayerHouse>(DZLDatabaseLayer.Get().GetPlayerHouse(sender.GetId())), true, sender);
                GetGame().RPCSingleParam(playerOpenBuy, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(dzlPlayer), true, sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_OPEN_SELL_BUILDING) {
            autoptr Param1<Building> paramSellHouse;
            if (ctx.Read(paramSellHouse)){
				DZLBuilding dzlBuildingSell = new DZLBuilding(paramSellHouse.param1);
                DZLHouseDefinition actualHouseDefSell = houseFinder.GetHouseDefinitionByBuilding(paramSellHouse.param1);
                string messageSell = "#error_sell_house";
                PlayerBase playerSellHouse = PlayerBase.Cast(target);
                DZLPlayer dzlPlayerSellHouse = playerSellHouse.GetDZLPlayer();

                if (actualHouseDefSell && dzlBuildingSell && dzlBuildingSell.IsOwner(playerSellHouse)) {
                    float sellPrice = actualHouseDefSell.sellPrice;

                    array<ref DZLStorageTypeBought> storages = dzlBuildingSell.GetStorage();
                    foreach(DZLStorageTypeBought storage: storages) {
                        if (!storage) continue;
                        houseFinder.objectFinder.DeleteContainerAt(storage.position, storage.position, storage.type, paramSellHouse.param1);

                        sellPrice += storage.sellPrice;
                    }

                    dzlBuildingSell.GetStorage().Clear();

                    dzlPlayerSellHouse.AddMoneyToPlayer(sellPrice);
                    dzlBuildingSell.SellOnServer(playerSellHouse);

                    messageSell = "#successfully_sell_house";
                    DZLLogHouseTrade(sender.GetId(), "sell house", sellPrice, dzlBuildingSell.GetDZLHouse().GetPosition());
                }
                GetGame().RPCSingleParam(playerSellHouse, DAY_Z_LIFE_OPEN_SELL_BUILDING_RESPONSE, new Param2<ref DZLBuilding, string>(dzlBuildingSell, messageSell), true, sender);
                GetGame().RPCSingleParam(playerSellHouse, DAY_Z_LIFE_GET_PLAYER_BUILDING_RESPONSE, new Param1<ref DZLPlayerHouse>(DZLDatabaseLayer.Get().GetPlayerHouse(sender.GetId())), true, sender);
                GetGame().RPCSingleParam(playerSellHouse, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(dzlPlayerSellHouse), true, sender);
            }
        }
    }
}
