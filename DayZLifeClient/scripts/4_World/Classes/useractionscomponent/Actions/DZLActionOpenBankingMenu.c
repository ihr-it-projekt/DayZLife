class DZLActionOpenBankingMenu: ActionInteractBase {
    void DZLActionOpenBankingMenu() {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
    }

    override void CreateConditionComponents() {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTCursor;
    }

    override string GetText() {
        return "#open_banking_menu";
    }

    override void OnStartClient(ActionData action_data) {
        super.OnStartClient(action_data);

        if(g_Game.GetUIManager().GetMenu() != NULL) return;

        action_data.m_Player.RequestUpdateDZLPlayer();
        g_Game.GetUIManager().ShowScriptedMenu(action_data.m_Player.GetBankingMenu(), NULL);

    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if(!target) return false;
        if(!target.GetObject()) return false;

        DZLBaseActionObject objectTarget = DZLBaseActionObject.Cast(target.GetObject());
        if(!objectTarget || !objectTarget.IsBank()) return false;

        return true;
    }

    override bool IsLockTargetOnUse() {
        return false;
    }
}
