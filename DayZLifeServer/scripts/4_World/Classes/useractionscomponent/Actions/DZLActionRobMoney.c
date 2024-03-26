modded class DZLActionRobMoney {
    override void OnEndServer(ActionData action_data) {
        PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
        PlayerBase player = action_data.m_Player;
        DZLPlayer dzlPlayer = player.GetDZLPlayer();

        if(!targetPlayer) return;

        DZLPlayer dzlTargetPlayer = targetPlayer.GetDZLPlayer();
        if(!dzlTargetPlayer) return;

        if(!dzlTargetPlayer.HasMoney()) return;

        dzlTargetPlayer.TransferFromPlayerToOtherPlayer(dzlPlayer);
        GetGame().RPCSingleParam(null, DZL_RPC.EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, player.GetIdentity());
        GetGame().RPCSingleParam(null, DZL_RPC.EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, targetPlayer.GetIdentity());
    }
}
