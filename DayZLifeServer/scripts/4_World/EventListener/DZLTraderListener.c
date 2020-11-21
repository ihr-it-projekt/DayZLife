class DZLTraderListener
{
    ref DZLTraderConfig config;

    void DZLTraderListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
        config = new DZLTraderConfig;
    }

    void ~DZLTraderListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_TRADE_ACTION) {
            autoptr Param4<ref array<ref DZLTraderType>, array<EntityAI>, ref DZLTraderPosition, PlayerBase> paramTrade;
            if (ctx.Read(paramTrade)){
                array<EntityAI> playerItems = paramTrade.param4.GetPlayerItems();
                int sum = 0;
                int countSellItems = 0;
                int countBuyItems = 0;


                foreach(string categoryName: paramTrade.param3.categoryNames) {
                    DZLTraderCategory category = config.categories.GetCatByName(categoryName);

                    if (!category) continue;
                    foreach(DZLTraderType type: category.items) {
                        foreach(DZLTraderType traderType: paramTrade.param1) {
                            if (traderType.type == type.type) {
                                sum += type.buyPrice;
                                countBuyItems++;
                            }
                        }

                        foreach(EntityAI item: paramTrade.param2) {
                            if (item.GetType() == type.type) {
                                sum -= type.sellPrice;
                                countSellItems++;
                            }
                        }
                    }
                }

                DZLPlayer dzlPlayer = new DZLPlayer(sender.GetId());
                string message = "#error_not_enough_money";

                if (countBuyItems == paramTrade.param1.Count() && countSellItems == paramTrade.param2.Count() && dzlPlayer.HasEnoughMoney(sum)) {
                    foreach(DZLTraderType _traderType: paramTrade.param1) {
                        Add(paramTrade.param4, _traderType.type);
                    }
                    foreach(EntityAI _item: paramTrade.param2) {
                        GetGame().ObjectDelete(_item);
                    }
                    dzlPlayer.AddMoneyToPlayer(sum * -1);

                    message = "#trade_was_successful";
                    GetGame().RPCSingleParam(target, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(dzlPlayer), true, sender);
                }

			    GetGame().RPCSingleParam(target, DAY_Z_LIFE_TRADE_ACTION_RESPONSE, new Param1<string>(message), true, sender);
            }
        }
    }


    private void Add(PlayerBase player, string type) {
        EntityAI item;
        InventoryLocation inventoryLocation = new InventoryLocation;

        if (player.GetInventory().FindFirstFreeLocationForNewEntity(type, FindInventoryLocationType.ANY, inventoryLocation)) {
            item = player.GetHumanInventory().CreateInInventory(type);
        } else if (!player.GetHumanInventory().GetEntityInHands()) {
            item = player.GetHumanInventory().CreateInHands(type);
        }

        if (!item) {
            item = player.SpawnEntityOnGroundPos(type, player.GetPosition());
        }
    }


}