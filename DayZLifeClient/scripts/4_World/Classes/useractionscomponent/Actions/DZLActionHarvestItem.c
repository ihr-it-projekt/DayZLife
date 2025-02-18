class DZLActionHarvestItem: ActionInteractBase {
    ref DZLJobConfig config;

    void DZLActionHarvestItem() {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_RESTRAINTARGET;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
    }

    override string GetText() {
        return "#start_work";
    }

    override void CreateConditionComponents() {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTNone;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        config = DZLConfig.Get().jobConfig;
        if(!config) return false;

        vector playerPosition = player.GetPosition();
        DZLWorkZone zone = config.FindZone(playerPosition);
        if(!zone) return false;
        m_CommandUID = zone.m_CommandUID;
        EntityAI item_in_hands_source = player.GetHumanInventory().GetEntityInHands();

        if(item_in_hands_source) {
            string handItemType = item_in_hands_source.GetType();
            handItemType.ToLower();
        }

        foreach(DZLHarvestItemToolRelation relation: zone.harvestItemToolRelation) {
            if(0 == relation.itemsThatNeededForHarvest.Count()) return true;
            if(!handItemType) return false;

            foreach(string itemToHarvest: relation.itemsThatNeededForHarvest) {
                itemToHarvest.ToLower();
                if(handItemType == itemToHarvest) {
                    if(g_Game.IsServer()) {
                        return 0 < item_in_hands_source.GetHealth();
                    }
                    return true;
                }
            }
        }
        return false;
    }

    override void OnEndClient(ActionData action_data) {
        if(g_Game.GetUIManager().GetMenu() != NULL) return;
        DZLHarvestProgressBar bar = action_data.m_Player.GetHarvestProgressBar();
        g_Game.GetUIManager().ShowScriptedMenu(bar, NULL);
    }

    override bool IsLockTargetOnUse() {
        return false;
    }

};
