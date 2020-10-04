modded class MissionServer {
	
	void MissionServer()
	{
        DebugMessageServerDZL("Load DayZLifeServer");
        SpawnDLHouse("15151 11 13858", "0 0 0", "HouseInfoPoint");
	}
	
	void ~MissionServer() {

	}


    private void SpawnDLHouse(vector position, vector orientation, string gameObjectName) {
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