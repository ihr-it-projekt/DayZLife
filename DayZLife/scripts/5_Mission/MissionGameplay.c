modded class MissionGameplay 
{
	ref DZLServerConfig config;
	
    void MissionGameplay() {
        DebugMessageDZL("Load Client");
        DZLBuyHouseMenu.ClearInstance();

        GetDayZGame().Event_OnRPC.Insert(HandleEvents);
		
		Param1<DayZPlayer> paramGetConfig = new Param1<DayZPlayer>(GetGame().GetPlayer());
        GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_EVENT_GET_CONFIG, paramGetConfig, true);
	}
	
	void ~MissionGameplay() {
        DZLBuyHouseMenu.ClearInstance();
	}

	void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
    		if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE) {
    			Param1 <ref DZLServerConfig> configParam;
    			if (ctx.Read(configParam)){
					config = configParam.param1;
    				DZLBuyHouseMenu.GetInstance(config);
    			}
    		}
    	}
}