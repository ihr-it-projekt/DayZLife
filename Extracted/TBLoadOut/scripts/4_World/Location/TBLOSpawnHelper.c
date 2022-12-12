class TBLOSpawnHelper
{

    static Object SpawnActionPoint(vector pos, vector orientation, string gameObjectName) {
        //pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
        Object game_obj = GetGame().CreateObject(gameObjectName, pos, false, false, true);
        if (!game_obj) {
           return null;
        }

        game_obj.SetAllowDamage(false);
        TBLOSpawnHelper.SetPositionAndOrientation(game_obj, pos, orientation);

        return game_obj;
    }

    static void SetPositionAndOrientation(Object game_obj, vector position, vector orientation) {
        game_obj.SetPosition(position);
        game_obj.SetOrientation(orientation);
        game_obj.SetOrientation(game_obj.GetOrientation()); //Collision fix
        game_obj.Update();
        game_obj.SetAffectPathgraph(true, false);
        if( game_obj.CanAffectPathgraph() ) {
            GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( GetGame().UpdatePathgraphRegionByObject, 100, false, game_obj );
        }
    }

}
