modded class MissionServer {

    ref DZLConfig config;

	void MissionServer()
	{
        DebugMessageServerDZL("Load DayZLifeServer");
        SpawnDZLHouse("15150 11 13861", "0 0 0", "HouseInfoPoint");

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
                GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE, new Param1<ref DZLConfig>(config), true, sender);
            }
        }
    }


    private void SpawnDZLHouse(vector position, vector orientation, string gameObjectName) {
        Building obj = GetGame().CreateObject(gameObjectName, position);
        if (!obj) {
            return;
        }

        obj.SetFlags( EntityFlags.STATIC, false );
        obj.SetPosition( position );
        obj.SetOrientation( orientation );
        obj.SetOrientation( obj.GetOrientation() ); //Collision fix
        obj.Update();
        obj.SetAffectPathgraph( true, false );
        DebugMessageServerDZL("Object placed");
        if(obj.CanAffectPathgraph()) GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().UpdatePathgraphRegionByObject, 100, false, obj);
    }

};