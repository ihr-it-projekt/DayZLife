class DZLPayCheck
{
    static void Check(PlayerBase player, DZLPaycheckConfig config) {
        int amount = 0;
        int onlineTime = 100000000;
        DZLPlayer dzlPlayer = player.GetDZLPlayer();
        if (dzlPlayer && dzlPlayer.IsActiveAsCop() && config.cop.amount > 0) {
            amount = config.cop.amount;
            onlineTime = config.cop.onlineMinutesForPay;
        } else if (dzlPlayer && dzlPlayer.IsActiveAsMedic() && config.medic.amount > 0) {
            amount = config.medic.amount;
            onlineTime = config.medic.onlineMinutesForPay;
        } else if (dzlPlayer && dzlPlayer.IsActiveAsCivil() && config.civil.amount > 0) {
            amount = config.civil.amount;
            onlineTime = config.civil.onlineMinutesForPay;
        }

        if (amount > 0) {
            dzlPlayer.UpdateOnlineTime();
            if(dzlPlayer.GetActiveOnlineTime() >= onlineTime) {
                dzlPlayer.ResetOnlineTime();
                DZLDatabaseLayer.Get().GetBank().AddMoney(amount);
                dzlPlayer.AddMoneyToPlayerBank(amount);
                GetGame().RPCSingleParam(player, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, player.GetIdentity());
                DZLSendMessage(player.GetIdentity(), "#you_recive_a_paycheck: " + amount);
            }
        }
    }
}
