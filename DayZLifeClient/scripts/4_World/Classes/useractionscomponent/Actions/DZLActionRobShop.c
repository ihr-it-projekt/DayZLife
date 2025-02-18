class DZLActionRobShop: ActionInteractBase {
    DZLCrimeConfig config;

    void DZLActionRobShop() {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
    }

    override string GetText() {
        return "#rob_shop";
    }

    override void CreateConditionComponents() {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new DZL_CCTActionObject;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        config = DZLConfig.Get().crimeConfig;
        if(!config) return false;

        DZLBaseActionObject objectTarget = DZLBaseActionObject.Cast(target.GetObject());
        if(!objectTarget || !objectTarget.IsShopActionPoint()) return false;

        EntityAI item_in_hands_source = player.GetHumanInventory().GetEntityInHands();
        if(!item_in_hands_source) return false;

        bool hasItem = false;
        foreach(string itemForRaid: config.robTools) {
            if(item_in_hands_source.GetType() == itemForRaid) {
                hasItem = true;
                break;
            }
        }

        if(!hasItem) return false;

        return true;

    }

    override void OnStartClient(ActionData action_data) {
        PlayerBase player = action_data.m_Player;

        if(player) {
            g_Game.RPCSingleParam(player, DZL_RPC.START_ROB_MONEY_FROM_SHOP, null, true);
        }
    }
    override bool IsLockTargetOnUse() {
        return false;
    }
};
