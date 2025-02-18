class DZLActionTakeRobtMoneyShop: ActionInteractBase {
    ref DZLCrimeConfig config;

    void DZLActionTakeRobtMoneyShop() {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
    }

    override string GetText() {
        return "#take_robt_money";
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


        return true;
    }

    override void OnStartClient(ActionData action_data) {
        PlayerBase player = action_data.m_Player;

        if(player) {
            g_Game.RPCSingleParam(player, DZL_RPC.PAY_ROB_MONEY_FROM_SHOP, null, true);
        }
    }
    override bool IsLockTargetOnUse() {
        return false;
    }
};
