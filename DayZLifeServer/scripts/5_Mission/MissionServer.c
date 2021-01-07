modded class MissionServer {

    private ref DZLEventManager manager;
	private ref Timer paycheckTimer;
	private ref DZLPayCheckController paycheckController;

	void MissionServer()
	{
        DebugMessageDZL("Load DayZLifeServer");
        manager = new DZLEventManager;
        paycheckController = new DZLPayCheckController;
		paycheckTimer = new Timer();
	}

	override void OnInit() {
        super.OnInit();
        DZLBankingLocationBuilder.Create();
        DZLLicenceLocationBuilder.Create();
        DZLTraderLocationBuilder.Create();
        DZLLoadOutLocationBuilder.Create();
        DZLGarageLocationBuilder.Create();
        DZLLockedHouses.OnServerStart();

        paycheckTimer.Run(60, paycheckController, "Check", null, true);
        DZLLicenceCheck.Get();
    }

	override PlayerBase OnClientNewEvent(PlayerIdentity identity, vector pos, ParamsReadContext ctx){
		PlayerBase player = super.OnClientNewEvent(identity, pos, ctx);
		
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_NEW_SPAWN_CLIENT, new Param1<string>(""), true, identity);
		
		return player;
	}
}
