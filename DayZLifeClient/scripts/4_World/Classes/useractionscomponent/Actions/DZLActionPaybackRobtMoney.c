class DZLActionPaybackRobtMoney: ActionInteractBase {

    void DZLActionPaybackRobtMoney() {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
    }

    override string GetText() {
        return "#payback_robt_money";
    }

    override void CreateConditionComponents() {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new DZL_CCTActionObject;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        DZLBaseActionObject objectTarget = DZLBaseActionObject.Cast(target.GetObject());
        if(!objectTarget || !objectTarget.IsBank()) return false;

        if(!player.GetDZLPlayer() || !player.GetDZLPlayer().IsActiveJob(DAY_Z_LIFE_JOB_COP)) return false;

        DZLBank bank = player.GetBank();

        if(!bank || bank.GetLastRaidMoney() == 0) return false;

        return true;
    }

};
