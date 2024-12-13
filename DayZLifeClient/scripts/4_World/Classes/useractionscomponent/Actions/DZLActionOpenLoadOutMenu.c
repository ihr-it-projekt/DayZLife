class DZLActionOpenLoadOutMenu: ActionInteractBase {
    void DZLActionOpenLoadOutMenu() {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
    }

    override void CreateConditionComponents() {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new DZL_CCTActionObject;
    }

    override string GetText() {
        return "#open_loadout_menu";
    }

    override void OnStartClient(ActionData action_data) {
        super.OnStartClient(action_data);

        if(g_Game.GetUIManager().GetMenu() != NULL) return;

        DZLLoadOutMenu menu = action_data.m_Player.GetLoadOutMenu();

        string job = action_data.m_Player.GetDZLPlayer().GetActiveJob();
        menu.SetCategories(DZLConfig.Get().jobConfig.GetLoadOuts(job).loadOutCategories);
        g_Game.GetUIManager().ShowScriptedMenu(menu, NULL);
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        DZLBaseActionObject objectTarget = DZLBaseActionObject.Cast(target.GetObject());
        if(!objectTarget) return false;

        DZLLoadoutActionObject loadOutObject = DZLLoadoutActionObject.Cast(objectTarget);
        if(!loadOutObject) return false;

        DZLPlayer dzlPlayer = player.GetDZLPlayer();
        if(!dzlPlayer || !DZLConfig.Get().jobConfig) return false;
        if(dzlPlayer.GetActiveJob() == DAY_Z_LIFE_JOB_CIVIL) return false;

        return true;
    }
}
