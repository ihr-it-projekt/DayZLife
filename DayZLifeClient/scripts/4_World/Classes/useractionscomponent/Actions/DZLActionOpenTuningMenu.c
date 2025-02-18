class DZLActionOpenTuningMenu: ActionInteractBase {
    void ActionOpenLoadOutMenu() {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
    }

    override void CreateConditionComponents() {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new DZL_CCTActionObject;
    }

    override string GetText() {
        return "#open_tuning_menu";
    }

    override void OnStartClient(ActionData action_data) {
        super.OnStartClient(action_data);

        if(g_Game.GetUIManager().GetMenu() != NULL) return;
        DZLTuningMenu menu = action_data.m_Player.GetTuningMenu();

        g_Game.GetUIManager().ShowScriptedMenu(menu, NULL);
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        DZLBaseActionObject objectTarget = DZLBaseActionObject.Cast(target.GetObject());
        if(!objectTarget || !objectTarget.IsTuningPoint()) return false;

        DZLPlayer dzlPlayer = player.GetDZLPlayer();
        if(!dzlPlayer) return false;

        DZLTuningConfig config = DZLConfig.Get().tuningConfig;
        if(!config) return false;


        return dzlPlayer.IsActiveJob(config.requiredJob);
    }
    override bool IsLockTargetOnUse() {
        return false;
    }
}
