class DZLSpawnHelper
{

    static bool SpawnContainer(vector position, vector orientation, string gameObjectName) {
        Container_Base obj = GetGame().CreateObject(gameObjectName, position);
        if (!obj) {
            return false;
        }

        obj.SetFlags( EntityFlags.STATIC, false );
        obj.SetPosition( position );
        obj.SetOrientation( orientation );
        obj.SetOrientation( obj.GetOrientation() ); //Collision fix
        obj.Update();
        obj.SetAffectPathgraph( true, false );
        DebugMessageServerDZL("Object placed");
        if(obj.CanAffectPathgraph()) GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().UpdatePathgraphRegionByObject, 100, false, obj);
		
		return true;
    }
}