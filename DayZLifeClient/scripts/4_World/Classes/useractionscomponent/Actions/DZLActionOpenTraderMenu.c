class DZLActionOpenTraderMenu: ActionInteractBase {
    void DZLActionOpenTraderMenu() {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
    }

    override void CreateConditionComponents() {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new DZL_CCTActionObject;
    }

    override string GetText() {
        return "#open_trader_menu";
    }

    override void OnStartClient(ActionData action_data) {
        super.OnStartClient(action_data);

        DZLTraderPosition position = action_data.m_Player.GetTraderByPosition();

        if(!position) return;

        if(!position.CanOpenWithJob(action_data.m_Player.GetDZLPlayer().GetActiveJob())) {
            action_data.m_Player.DisplayMessage("#You_can_only_open_when_you_are_a: " + "#" + position.forJob);
            return;
        }

        if(g_Game.GetUIManager().GetMenu() != NULL) return;

        g_Game.GetUIManager().ShowScriptedMenu(action_data.m_Player.GetTraderMenu(position), NULL);
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        DZLBaseActionObject objectTarget = DZLBaseActionObject.Cast(target.GetObject());
        if(!objectTarget || !objectTarget.IsTrader()) return false;

        return true;
    }
}
