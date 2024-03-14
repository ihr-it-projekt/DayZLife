class ActionRobMoney: ActionInteractBase {
    void ActionRobMoney() {
        m_CommandUID = DayZPlayerConstants.CMD_GESTUREFB_COME;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
    }

    override void CreateConditionComponents() {
        m_ConditionTarget = new CCTMan;
        m_ConditionItem = new CCINone;
    }

    override string GetText() {
        return "#rob_money";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if(!DZLConfig.Get() || DZLConfig.Get().bankConfig || DZLConfig.Get().bankConfig.useMoneyAsObject) return false;

        PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());

        return targetPlayer.IsRestrained() || targetPlayer.IsUnconscious();
    }

    override void OnEndServer(ActionData action_data) {
        PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
        PlayerBase player = action_data.m_Player;
        DZLPlayer dzlPlayer = player.GetDZLPlayer();

        if(targetPlayer.IsRestrained() || targetPlayer.IsUnconscious()) {
            if(!targetPlayer && !targetPlayer.GetDZLPlayer()) return;

            DZLPlayer dzlTargetPlayer = targetPlayer.GetDZLPlayer();
            if(dzlTargetPlayer && dzlTargetPlayer.HasMoney()) {
                dzlTargetPlayer.TransferFromPlayerToOtherPlayer(dzlPlayer);

                GetGame().RPCSingleParam(null, DZL_RPC.EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, player.GetIdentity());
                GetGame().RPCSingleParam(null, DZL_RPC.EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, targetPlayer.GetIdentity());
            }
        }
    }
}
