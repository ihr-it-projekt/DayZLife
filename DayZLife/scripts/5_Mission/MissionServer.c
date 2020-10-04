modded class MissionServer {
	
	void MissionServer()
	{
	    DebugMessageDZL("Load Server on client");
        SpawnObject("HouseInfoPoint", "15151 10 13858", "0 0 0");
	}
	
	void ~MissionServer() {

	}

    private void SpawnDLHouse(vector position, vector orientation, string gameObjectName) {
         auto obj = GetGame().CreateObject_WIP( type, position, ECE_CREATEPHYSICS );
        obj.SetFlags( EntityFlags.STATIC, false );
        obj.SetPosition( position );
        obj.SetOrientation( orientation );
        obj.SetOrientation( obj.GetOrientation() ); //Collision fix
        obj.Update();
        obj.SetAffectPathgraph( true, false );
        if( obj.CanAffectPathgraph() ) GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( GetGame().UpdatePathgraphRegionByObject, 100, false, obj );
    }
 };