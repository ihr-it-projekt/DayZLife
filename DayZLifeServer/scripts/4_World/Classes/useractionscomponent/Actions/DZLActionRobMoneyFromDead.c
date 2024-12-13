modded class DZLActionRobMoneyFromDead {

    override void OnEndServer(ActionData action_data) {
        PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
        PlayerBase player = action_data.m_Player;
        DZLPlayer dzlPlayer = player.GetDZLPlayer();

        if(!targetPlayer.IsAlive() && targetPlayer.GetMoneyPlayerIsDead() > 0) {
            targetPlayer.TransferFromDeadPlayer(dzlPlayer);

            g_Game.RPCSingleParam(null, DZL_RPC.EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, player.GetIdentity());
        }
    }

}
