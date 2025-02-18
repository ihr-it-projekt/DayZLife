class DZLActionRobMoneyFromDead: ActionInteractBase {
    void DZLActionRobMoneyFromDead() {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
    }

    override void CreateConditionComponents() {
        m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT, false);
        m_ConditionItem = new CCINone;
    }

    override string GetText() {
        return "#rob_money";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());
        if(!targetPlayer) return false;
        if(targetPlayer.IsAlive()) return false;
        if(targetPlayer.GetMoneyPlayerIsDead() <= 0) return false;

        DZLConfig config = DZLConfig.Get();
        if(!config || config.bankConfig || config.bankConfig.useMoneyAsObject) return false;

        return true;
    }

    override void OnEndClient(ActionData action_data) {
        PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
        targetPlayer.SetMoneyPlayerIsDead(0);
    }
    override bool IsLockTargetOnUse() {
        return false;
    }
}
