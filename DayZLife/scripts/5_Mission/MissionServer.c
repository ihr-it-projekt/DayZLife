modded class MissionServer {

	void MissionServer() {
        DebugMessageDZL("Load DayZLifeServer Client");
	}

	override void OnInit() {
	    super.OnInit();
        DZLLicenceCheck.Get();
    }
}
