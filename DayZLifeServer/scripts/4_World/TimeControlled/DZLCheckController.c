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

        if (countRun > 29) {
            array<Man> allPlayers = new array<Man>;
            GetGame().GetPlayers(allPlayers);
            foreach(Man playerMan: allPlayers) {
                PlayerBase player = PlayerBase.Cast(playerMan);
                if (!player)   continue;
                PlayerIdentity playerIdent = player.GetIdentity();

                DZLPayCheck.Check(player, config.jobConfig.paycheck);
            }
        }

        DZLInsuranceManager.Get().Check();

        if (countRun > 29) {
            countRun = 0;
        }
	}
}
