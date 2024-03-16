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
        DZLTunerPosition tunerPosition = action_data.m_Player.GetTunerPositionByPosition();

        if(!tunerPosition) return;

        menu.SetPosition(tunerPosition);

        GetGame().GetUIManager().ShowScriptedMenu(menu, NULL);
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        DZLBaseActionObject objectTarget = DZLBaseActionObject.Cast(target.GetObject());
        if(!objectTarget || !objectTarget.IsTuningPoint()) return false;

        DZLTunerPosition tunerPosition = player.GetTunerPositionByPosition();

        return tunerPosition && tunerPosition.PlayerCanDoActions(player.GetPlayerId());
    }
}
