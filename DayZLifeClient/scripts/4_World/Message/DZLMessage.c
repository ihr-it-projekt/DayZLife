static void DZLSendMessage(PlayerIdentity player, string message) {
    if(player) {
        g_Game.RPCSingleParam(null, DZL_RPC.RECEIVE_MESSAGE, new Param1<string>(message), true, player);
    } else {
        array<Man> _players = new array<Man>;
        g_Game.GetPlayers(_players);
        if(_players) {
            foreach(Man _player: _players) {
                g_Game.RPCSingleParam(_player, DZL_RPC.RECEIVE_MESSAGE, new Param1<string>(message), true, _player.GetIdentity());
            }
        }
    }
}

static void DZLSendMedicMessage(string message) {
    array<Man> _players = new array<Man>;
    g_Game.GetPlayers(_players);
    if(_players) {
        foreach(Man _player: _players) {
            PlayerBase receiver = PlayerBase.Cast(_player);
            if(receiver.GetDZLPlayer().IsActiveJob(DAY_Z_LIFE_JOB_MEDIC)) {
                g_Game.RPCSingleParam(receiver, DZL_RPC.RECEIVE_MEDIC_MESSAGE, new Param1<string>(message), true, receiver.GetIdentity());
            }
        }
    }
}

