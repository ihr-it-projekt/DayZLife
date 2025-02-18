class DZLActionOpenArrestMenu: ActionInteractBase {
    void DZLActionOpenArrestMenu() {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_HUDCursorIcon = CursorIcons.CloseHood;
    }

    override void CreateConditionComponents() {
        m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT, false);
        m_ConditionItem = new CCINone;
    }

    override string GetText() {
        return "#give_arrest";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if(!target.GetObject()) return false;
        PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());
        if(!targetPlayer) return false;

        DZLPlayer dzlPlayerCop = player.GetDZLPlayer();
        if(dzlPlayerCop.arrestTimeInMinutes != 0) return false;
        if(!dzlPlayerCop.IsActiveJob(DAY_Z_LIFE_JOB_COP) && !dzlPlayerCop.IsActiveJob(DAY_Z_LIFE_JOB_ARMY)) return false;

        if(!targetPlayer.IsDZLPlayer()) return false;

        return true;
    }

    override void OnStartClient(ActionData action_data) {
        if(g_Game.GetUIManager().GetMenu() != NULL) return;
        PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
        PlayerBase player = action_data.m_Player;
        DZLPlayerArrestMenu menu = player.GetArrestMenu();
        menu.SetReceiver(targetPlayer);
        g_Game.GetUIManager().ShowScriptedMenu(menu, NULL);
    }
    override bool IsLockTargetOnUse() {
        return false;
    }
}
