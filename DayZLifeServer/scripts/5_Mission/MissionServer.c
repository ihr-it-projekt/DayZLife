modded class MissionServer {

    ref DZLConfig config;

	void MissionServer()
	{
        DebugMessageServerDZL("Load DayZLifeServer");
        config = new DZLConfig;

        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
	}
	
	void ~MissionServer() {

	}

	void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG) {
            autoptr Param1<PlayerBase> paramGetConfig;
            if (ctx.Read(paramGetConfig)){
				DebugMessageServerDZL("Send Config");
	
				DebugMessageServerDZL("DZLMoneyConfig config: " + config.moneyConfig.currencyValues.Count().ToString());
				DebugMessageServerDZL("DZLHouseConfig config: " + config.houseConfig.houseConfigs.Count().ToString());
				

                GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE, new Param1<ref DZLConfig>(config), true, sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_OPEN_GET_BUILDING_DATA) {
            autoptr Param2<PlayerBase, ref Building> paramGetBuildingProperties;
            if (ctx.Read(paramGetBuildingProperties)){
				DebugMessageServerDZL("Get Building DATA " + paramGetBuildingProperties.param2.GetPosition().ToString());
	
                GetGame().RPCSingleParam(paramGetBuildingProperties.param1, DAY_Z_LIFE_OPEN_GET_BUILDING_DATA_RESPONSE, new Param1<ref DZLBuilding>(new DZLBuilding(paramGetBuildingProperties.param2)), true, sender);
            }
        }
    }

};