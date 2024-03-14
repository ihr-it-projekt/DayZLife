class DZLPayCheck {
    static void Check(PlayerBase player, DZLPaycheckConfig paycheckConfig) {
        int amount = 0;
        int onlineTime = 100000000;
        DZLPlayer dzlPlayer = player.GetDZLPlayer();
        DZLPaycheck payCheck = DZLRankHelper.getCurrentPayCheck(dzlPlayer, paycheckConfig);
        amount = payCheck.amount;
        onlineTime = payCheck.onlineMinutesForPay;

        if(amount > 0) {
            dzlPlayer.UpdateOnlineTime();
            if(dzlPlayer.GetActiveOnlineTime() >= onlineTime) {
                dzlPlayer.ResetOnlineTime();
                DZLDatabaseLayer.Get().GetBank().AddMoney(amount);
                dzlPlayer.AddMoneyToPlayerBank(amount);
                GetGame().RPCSingleParam(null, DZL_RPC.EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, player.GetIdentity());
                DZLSendMessage(player.GetIdentity(), "#you_recive_a_paycheck: " + amount);
            }
        }
    }
}
