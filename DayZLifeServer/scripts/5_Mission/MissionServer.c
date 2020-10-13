modded class MissionServer {

    ref DZLEventManager manager;

	void MissionServer()
	{
        DebugMessageServerDZL("Load DayZLifeServer");
        manager = new DZLEventManager;
	}
};