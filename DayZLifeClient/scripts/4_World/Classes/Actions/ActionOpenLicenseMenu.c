class ActionOpenLicenseMenu: ActionInteractBase {
    void ActionOpenLicenseMenu() {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
    }

    override void CreateConditionComponents() {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new DZL_CCTActionObject;
    }

    override string GetText() {
        return "#open_licence_menu";
    }

    override void OnStartClient(ActionData action_data) {
        super.OnStartClient(action_data);

        if(g_Game.GetUIManager().GetMenu() == NULL) {
            GetGame().GetUIManager().ShowScriptedMenu(action_data.m_Player.GetLicenceMenu(), NULL);
        }
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        DZLBaseActionObject objectTarget = DZLBaseActionObject.Cast(target.GetObject());
        if(!objectTarget || !objectTarget.IsLicensePoint()) return false;

        if(!DZLConfig.Get().licenceConfig) return false;

        return true;
    }
}
