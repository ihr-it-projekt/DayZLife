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
		
		Param1<string> param = new Param1<string>("");
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_NEW_SPAWN_CLIENT, param, true, identity);
		
		return player;
	}
}
