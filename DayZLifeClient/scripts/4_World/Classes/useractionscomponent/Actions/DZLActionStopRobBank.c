class DZLActionStopRobBank: ActionInteractBase {
    ref DZLBankingConfig config;

    void DZLActionStopRobBank() {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
    }

    override string GetText() {
        return "#stop_rob_bank";
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

        return true;
    }

};
