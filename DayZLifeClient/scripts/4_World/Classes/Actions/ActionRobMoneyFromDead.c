class ActionRobMoneyFromDead: ActionInteractBase {
    void ActionRobMoney() {
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
        if(!DZLConfig.Get() || DZLConfig.Get().bankConfig || DZLConfig.Get().bankConfig.useMoneyAsObject) return false;
        return PlayerBase.Cast(target.GetObject()).GetMoneyPlayerIsDead() > 0;
    }

    override void OnEndServer(ActionData action_data) {
        PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
        PlayerBase player = action_data.m_Player;
        DZLPlayer dzlPlayer = player.GetDZLPlayer();

        if(!targetPlayer.IsAlive() && targetPlayer.GetMoneyPlayerIsDead() > 0) {
            targetPlayer.TransferFromDeadPlayer(dzlPlayer);

            GetGame().RPCSingleParam(null, DZL_RPC.EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, player.GetIdentity());
        }
    }

    override void OnEndClient(ActionData action_data) {
        PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
        targetPlayer.SetMoneyPlayerIsDead(0);
    }
}
