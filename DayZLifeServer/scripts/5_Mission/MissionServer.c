modded class MissionServer {

    ref DZLEventManager manager;

	void MissionServer()
	{
        DebugMessageDZL("Load DayZLifeServer");
        manager = new DZLEventManager;

	}

	override void OnInit() {
        super.OnInit();
        DZLBankingLocationBuilder.Create();
        DZLLicenceLocationBuilder.Create();
        DZLTraderLocationBuilder.Create();
    }
};