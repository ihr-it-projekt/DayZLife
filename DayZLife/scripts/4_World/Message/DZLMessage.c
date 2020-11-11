static void DZLSendMessage(PlayerIdentity player, string message) {
    GetGame().RPCSingleParam(null, DAY_Z_LIFE_RECEIVE_MESSAGE, new Param1<string>(message), true, player);
}