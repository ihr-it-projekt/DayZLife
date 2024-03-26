class DZLActionRobMoney: ActionInteractBase {
    void DZLActionRobMoney() {
        m_CommandUID = DayZPlayerConstants.CMD_GESTUREFB_COME;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
    }

    override void CreateConditionComponents() {
        m_ConditionTarget = new CCTMan;
        m_ConditionItem = new CCINone;
    }

    override string GetText() {
        return "#rob_money";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if(!DZLConfig.Get() || DZLConfig.Get().bankConfig || DZLConfig.Get().bankConfig.useMoneyAsObject) return false;

        PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());

        return targetPlayer.IsRestrained() || targetPlayer.IsUnconscious();
    }
}
