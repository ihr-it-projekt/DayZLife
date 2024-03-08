class ActionOpenLoadOutMenu: ActionInteractBase {
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
        return "#open_loadout_menu";
    }

    override void OnStartClient(ActionData action_data) {
        super.OnStartClient(action_data);

        if(g_Game.GetUIManager().GetMenu() == NULL) {
            DZLLoadOutMenu menu = action_data.m_Player.GetLoadOutMenu();
            if(action_data.m_Player.GetDZLPlayer().HasJob(DAY_Z_LIFE_JOB_COP)) {
                menu.SetCategories(action_data.m_Player.GetConfig().jobConfig.loadOutsCops.loadOutCategories);
            } else if(action_data.m_Player.GetDZLPlayer().HasJob(DAY_Z_LIFE_JOB_MEDIC)) {
                menu.SetCategories(action_data.m_Player.GetConfig().jobConfig.loadOutsMedics.loadOutCategories);
            } else if(action_data.m_Player.GetDZLPlayer().HasJob(DAY_Z_LIFE_JOB_TRANSPORT)) {
                menu.SetCategories(action_data.m_Player.GetConfig().jobConfig.loadOutsTransport.loadOutCategories);
            } else if(action_data.m_Player.GetDZLPlayer().HasJob(DAY_Z_LIFE_JOB_ARMY)) {
                menu.SetCategories(action_data.m_Player.GetConfig().jobConfig.loadOutsArmy.loadOutCategories);
            }

            GetGame().GetUIManager().ShowScriptedMenu(menu, NULL);
        }
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        DZLBaseActionObject objectTarget = DZLBaseActionObject.Cast(target.GetObject());
        if(!objectTarget || !objectTarget.IsLoadOut()) return false;

        DZLPlayer dzlPlayer = player.GetDZLPlayer();
        if(!dzlPlayer || !player.GetConfig() || !player.GetConfig().jobConfig) return false;

        if(dzlPlayer.HasJob(DAY_Z_LIFE_JOB_COP)) {
            return objectTarget.IsCopLoadOut();
        } else if(dzlPlayer.HasJob(DAY_Z_LIFE_JOB_MEDIC)) {
            return objectTarget.IsMedicLoadOut();
        } else if(dzlPlayer.HasJob(DAY_Z_LIFE_JOB_TRANSPORT)) {
            return objectTarget.IsTransportLoadOut();
        } else if(dzlPlayer.HasJob(DAY_Z_LIFE_JOB_ARMY)) {
            return objectTarget.IsArmyLoadOut();
        }

        return false;
    }
}
