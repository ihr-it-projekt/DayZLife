class DZLPayCheckController
{
    DZLPaycheckConfig config;

    void DZLPayCheckController() {
        config = DZLConfig.Get().jobConfig.paycheck;
    }
	
	void Check() {
	    if (!DZLLicenceCheck.Get().HasActiveLicence(null)) return;
		array<Man> allPlayers = new array<Man>;
        GetGame().GetPlayers(allPlayers);
		
		foreach(Man player: allPlayers) {
		
			DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(player.GetIdentity().GetId());

			int amount = 0;
			int onlineTime = 100000000;
			
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
                    dzlPlayer.AddMoneyToPlayerBank(amount);
                    GetGame().RPCSingleParam(player, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(dzlPlayer), true, player.GetIdentity());
                    DZLSendMessage(player.GetIdentity(), "#you_recive_a_paycheck: " + amount);
                }
			}
		}
	}
}
