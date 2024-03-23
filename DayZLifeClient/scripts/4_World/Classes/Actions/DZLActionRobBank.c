class DZLActionRobBank: ActionInteractBase {
    ref DZLBankingConfig config;

    void DZLActionRobBank() {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
    }

    override string GetText() {
        return "#rob_bank";
    }

    override void CreateConditionComponents() {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new DZL_CCTActionObject;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        config = DZLConfig.Get().bankConfig;
        if(!config) return false;

        DZLBaseActionObject objectTarget = DZLBaseActionObject.Cast(target.GetObject());

        if(!objectTarget || !objectTarget.IsBank()) return false;

        if(!config) return false;

        EntityAI item_in_hands_source = player.GetHumanInventory().GetEntityInHands();

        if(!item_in_hands_source) return false;

        bool hasItem = false;
        foreach(string itemForRaid: config.itemsCanUsedToRaidBank) {
            if(item_in_hands_source.GetType() == itemForRaid) {
                hasItem = true;
                break;
            }
        }

        if(!hasItem) return false;

        if(!isInNearOfBankAndLocationIsEnabled(player)) return false;

        return true;
    }

    protected bool isInNearOfBankAndLocationIsEnabled(PlayerBase player) {
        if(!player) {
            return false;
        }
        vector playerPosition = player.GetPosition();
        if(!playerPosition) {
            return false;
        }
        foreach(DZLBankingPosition position: config.positionOfBankingPoints) {
            if(position && position.position && vector.Distance(position.position, playerPosition) <= config.maximumRaidDistanceToBank) {
                return position.raidIsEnabled;
            }
        }
        return false;
    }

};
