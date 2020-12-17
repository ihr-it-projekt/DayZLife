class DZLPayCheckController
{
    DZLPaycheckConfig config;

    void DZLPayCheckController() {
        config = DZLConfig.Get().jobConfig.paycheck;
    }
	
	void Check() {
		array<Man> allPlayers = new array<Man>;
        GetGame().GetPlayers(allPlayers);
		
		foreach(Man player: allPlayers) {
		
			DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(player.GetIdentity().GetId());

			int amount = 0;
			int onlineTime = 100000000;
			
			if (dzlPlayer && dzlPlayer.activeJob == DAY_Z_LIFE_JOB_COP && config.cop.amount > 0) {
			    amount = config.cop.amount;
                onlineTime = config.cop.onlineMinutesForPay;
			} else if (dzlPlayer && dzlPlayer.activeJob == DAY_Z_LIFE_JOB_MEDIC && config.medic.amount > 0) {
			    amount = config.medic.amount;
                onlineTime = config.medic.onlineMinutesForPay;
			} else if (dzlPlayer && dzlPlayer.activeJob == DAY_Z_LIFE_JOB_CIVIL && config.civil.amount > 0) {
			    amount = config.civil.amount;
                onlineTime = config.civil.onlineMinutesForPay;
			}

			if (amount > 0) {
			    dzlPlayer.UpdateOnlineTime();
			    if(dzlPlayer.GetActiveOnlineTime() >= onlineTime) {
                    dzlPlayer.ResetOnlineTime();
                    dzlPlayer.AddMoneyToPlayer(amount);
                }
			}
		}
	}
}
