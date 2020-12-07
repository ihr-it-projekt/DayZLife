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

        DZLLockedHouses.OnServerStart();
    }
	
	override PlayerBase OnClientNewEvent(PlayerIdentity identity, vector pos, ParamsReadContext ctx){
		PlayerBase player = super.OnClientNewEvent(identity, pos, ctx);
		
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_NEW_SPAWN_CLIENT, new Param1<string>(""), true, identity);
		
		return player;
	}
}
