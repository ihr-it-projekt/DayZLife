modded class MissionServer {

    private ref DZLEventManager manager;
	private ref Timer databaseTimer;
	private ref Timer paycheckTimer;
	private ref DZLPayCheckController paycheckController;

	void MissionServer()
	{
        DebugMessageDZL("Load DayZLifeServer");
        manager = new DZLEventManager;
        paycheckController = new DZLPayCheckController;
		databaseTimer = new Timer();
		paycheckTimer = new Timer();
	}

	void ~MissionServer() {
	    DZLDatabaseLayer.Get().Save();
	}

	override void OnInit() {
        super.OnInit();
        DZLBankingLocationBuilder.Create();
        DZLLicenceLocationBuilder.Create();
        DZLTraderLocationBuilder.Create();
        DZLLoadOutLocationBuilder.Create();
        DZLLockedHouses.OnServerStart();

        databaseTimer.Run(20, DZLDatabaseLayer.Get(), "Save", null, true);
        paycheckTimer.Run(60, paycheckController, "Check", null, true);
        DZLLicenceCheck.Get();
    }
	
	override PlayerBase OnClientNewEvent(PlayerIdentity identity, vector pos, ParamsReadContext ctx){
		PlayerBase player = super.OnClientNewEvent(identity, pos, ctx);
		
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_NEW_SPAWN_CLIENT, new Param1<string>(""), true, identity);
		
		return player;
	}
}
