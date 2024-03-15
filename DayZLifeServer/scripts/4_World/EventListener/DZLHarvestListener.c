class DZLHarvestListener: DZLBaseEventListener {

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.HARVEST) {
            PlayerBase player = PlayerBase.Cast(target);
            DZLJobConfig config = DZLConfig.Get().jobConfig;
            DZLWorkZone zone = config.FindZone(player.GetPosition());
            if(zone) {
                EntityAI item_in_hands_source = player.GetHumanInventory().GetEntityInHands();
                array<DZLHarvestItemToolRelation> matchedRelations = new array<DZLHarvestItemToolRelation>;
                if(item_in_hands_source) {
                    string handItemType = item_in_hands_source.GetType();
                    handItemType.ToLower();
                }

                foreach(DZLHarvestItemToolRelation relation: zone.harvestItemToolRelation) {
                    if(0 == relation.itemsThatNeededForHarvest.Count()) {
                        matchedRelations.Insert(relation);
                        continue;
                    }
                    foreach(string itemsThatNeededForHarvest: relation.itemsThatNeededForHarvest) {
                        itemsThatNeededForHarvest.ToLower();
                        if(item_in_hands_source && handItemType == itemsThatNeededForHarvest) {
                            if(0 < item_in_hands_source.GetHealth()) {
                                matchedRelations.Insert(relation);
                            }
                        }
                    }
                }

                if(matchedRelations.Count() == 0) return;

                DZLHarvestItemToolRelation randRelation = matchedRelations.GetRandomElement();

                if(!randRelation) return;

                string randomItemType = randRelation.itemsThatCanHarvest.GetRandomElement();

                InventoryLocation inventoryLocation = new InventoryLocation;
                EntityAI item;

                bool spaceLeft = true;

                if(player.GetInventory().FindFirstFreeLocationForNewEntity(randomItemType, FindInventoryLocationType.ANY, inventoryLocation)) {
                    item = player.GetHumanInventory().CreateInInventory(randomItemType);
                } else if(!player.GetHumanInventory().GetEntityInHands()) {
                    item = player.GetHumanInventory().CreateInHands(randomItemType);
                } else {
                    spaceLeft = false;
                    DZLSendMessage(player.GetIdentity(), "#no_space_left_in_inventory");
                }

                if(item) {
                    DZLSendMessage(player.GetIdentity(), "#you_got: " + DZLDisplayHelper.GetItemDisplayName(randomItemType));
                    DZLLogCrafting(sender.GetId(), "harvest get item", randomItemType);
                    player.isOnHarvest = false;
                } else if(!item && spaceLeft) {
                    DZLLogCrafting(sender.GetId(), "harvest get NO item but has space", randomItemType);
                }

                if(item_in_hands_source) {
                    item_in_hands_source.SetHealth(item_in_hands_source.GetHealth() - zone.damagePerHarvestItem);
                }
            }
        }
    }
}
