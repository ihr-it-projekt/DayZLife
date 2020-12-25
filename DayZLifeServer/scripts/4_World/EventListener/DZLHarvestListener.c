class DZLHarvestListener
{
    DZLJobConfig config;
    void DZLHarvestListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
        config = DZLConfig.Get().jobConfig;
    }

    void ~DZLHarvestListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (!DZLLicenceCheck.Get().HasActiveLicence(sender)) return;
        if (rpc_type == DAY_Z_LIFE_HARVEST) {
            autoptr Param1<PlayerBase> paramHarvest;
            if (ctx.Read(paramHarvest)){
                PlayerBase player = paramHarvest.param1;

                DZLWorkZone zone = config.FindZone(player.GetPosition());
                if (zone) {
                    EntityAI item_in_hands_source = player.GetHumanInventory().GetEntityInHands();
                    array<DZLHarvestItemToolRelation> matchedRelations = new array<DZLHarvestItemToolRelation>;
                    if(item_in_hands_source) {
                        string handItemType = item_in_hands_source.GetType();
                        handItemType.ToLower();
                    }

                    foreach(DZLHarvestItemToolRelation relation: zone.harvestItemToolRelation) {
                        if (0 == relation.itemsThatNeededForHarvest.Count()) {
                            matchedRelations.Insert(relation);
                            continue;
                        }
                        foreach(string _item: relation.itemsThatNeededForHarvest) {
                            _item.ToLower();
                             if (item_in_hands_source && handItemType == _item) {
                                if (0 < item_in_hands_source.GetHealth()) {
                                    matchedRelations.Insert(relation);
                                }
                            }
                        }
                    }

                    if (matchedRelations.Count() == 0) return;

                    DZLHarvestItemToolRelation randRelation = matchedRelations.GetRandomElement();

                    if (!randRelation) return;

                    string randomItemType = randRelation.itemsThatCanHarvest.GetRandomElement();

                    InventoryLocation inventoryLocation = new InventoryLocation;
                    EntityAI item;

                    if (player.GetInventory().FindFirstFreeLocationForNewEntity(randomItemType, FindInventoryLocationType.ANY, inventoryLocation)) {
                        item = player.GetHumanInventory().CreateInInventory(randomItemType);
                    } else if (!player.GetHumanInventory().GetEntityInHands()) {
                        item = player.GetHumanInventory().CreateInHands(randomItemType);
                    } else {
                        DZLSendMessage(player.GetIdentity(), "#no_space_left_in_inventory");
                    }

                    if (item) {
                        DZLSendMessage(player.GetIdentity(), "#you_got: " + DZLDisplayHelper.GetItemDisplayName(randomItemType));
                        player.isOnHarvest = false;
                    }

                    if (item_in_hands_source) {
                        item_in_hands_source.SetHealth(item_in_hands_source.GetHealth() - zone.damagePerHarvestItem);
                    }
                }
            }
        }
    }
}
