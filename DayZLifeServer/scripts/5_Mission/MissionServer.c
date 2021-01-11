modded class MissionServer {

    private ref DZLEventManager manager;
    private ref DZLBuilderManager builderManager;
	private ref Timer paycheckTimer;
	private ref DZLCheckController checkController;

	void MissionServer() {
        DebugMessageDZL("Load DayZLifeServer");
        paycheckTimer = new Timer;
	}

	override void OnInit() {
	    super.OnInit();
		DZLDatabase database = DZLSpawnHelper.SpawnDataBase();
		if (database) {
            manager = new DZLEventManager;
            builderManager = new DZLBuilderManager;
            checkController = new DZLCheckController;

            DZLLockedHouses.OnServerStart();
            paycheckTimer.Run(1, checkController, "Check", null, true);
            builderManager.Create();
        }
    }

	override PlayerBase OnClientNewEvent(PlayerIdentity identity, vector pos, ParamsReadContext ctx){
		PlayerBase player = super.OnClientNewEvent(identity, pos, ctx);
		
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_NEW_SPAWN_CLIENT, new Param1<string>(""), true, identity);
		
		return player;
	}
}
