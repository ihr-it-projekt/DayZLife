class DZLBuilderManager
{
	private ref DZLPayCheckController paycheckController;
	private ref DZLBankingLocationBuilder bankingBuilder;
	private ref DZLLicenceLocationBuilder licenceBuilder;
	private ref DZLTraderLocationBuilder traderBuilder;
	private ref DZLLoadOutLocationBuilder loadOutBuilder;
	private ref DZLGarageLocationBuilder garageBuilder;

	private ref Timer checkTimer;

	void DZLBuilderManager() {
	    checkTimer = new Timer;
	    bankingBuilder = new DZLBankingLocationBuilder();
        licenceBuilder = new DZLLicenceLocationBuilder();
        traderBuilder = new DZLTraderLocationBuilder();
        loadOutBuilder = new DZLLoadOutLocationBuilder();
        garageBuilder = new DZLGarageLocationBuilder();
        checkTimer.Run(60, this, "Check", null, true);
	}

	void Create(){
	    bankingBuilder.Create();
        licenceBuilder.Create();
        traderBuilder.Create();
        loadOutBuilder.Create();
        garageBuilder.Create();
	}

	void Check(){
	    bankingBuilder.CheckPosition();
        licenceBuilder.CheckPosition();
        traderBuilder.CheckPosition();
        loadOutBuilder.CheckPosition();
        garageBuilder.CheckPosition();
	}
}
