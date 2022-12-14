static void TBMSendMessage(PlayerIdentity player, string message) {
    if (player) {
        GetGame().RPCSingleParam(null, DAY_Z_LIFE_RECEIVE_MESSAGE, new Param1<string>(message), true, player);
    } else {
        array<Man> _players = new array<Man>;
        GetGame().GetPlayers(_players);
        if (_players) {
            foreach(Man _player: _players) {
                GetGame().RPCSingleParam(_player, DAY_Z_LIFE_RECEIVE_MESSAGE, new Param1<string>(message), true, _player.GetIdentity());
            }
        }
    }
}


