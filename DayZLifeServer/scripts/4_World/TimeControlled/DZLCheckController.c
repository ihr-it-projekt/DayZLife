class DZLCheckController
{
    DZLConfig config;
    private int countRun;

    void DZLCheckController() {
        config = DZLConfig.Get();
		countRun = 0;
    }
	
	void Check() {
	    ++countRun;
	    if (!DZLLicenceCheck.Get().HasActiveLicence(null)) return;
        array<Man> allPlayers = new array<Man>;
        GetGame().GetPlayers(allPlayers);

        foreach(Man playerMan: allPlayers) {
			PlayerBase player = PlayerBase.Cast(playerMan);
			if (!player) {
			    LogMessageDZL("Check player not casted");
			    continue;
			}
			PlayerIdentity playerIdent = player.GetIdentity();

            DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(playerIdent.GetId());
			if(!dzlPlayer) {
				LogMessageDZL("Check playerdzl not found");
				continue;
			}

			if (countRun > 29) {
                DZLPayCheck.Check(dzlPlayer, player, config.jobConfig.paycheck);
                countRun = 0;
			}

			DZLMedicHealth.CheckHealth(dzlPlayer, player, playerIdent);
        }
	}
}
