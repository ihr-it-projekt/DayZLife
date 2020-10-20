modded class MissionServer {

    ref DZLEventManager manager;

	void MissionServer()
	{
        DebugMessageServerDZL("Load DayZLifeServer");
        manager = new DZLEventManager;

	}

	override void OnInit() {
        super.OnInit();
        DZLBankingLocationBuilder.Create();
    }
};