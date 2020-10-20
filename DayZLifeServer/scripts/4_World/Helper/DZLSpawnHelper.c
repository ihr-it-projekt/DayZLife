class DZLSpawnHelper
{

    static bool SpawnContainer(vector position, vector orientation, string gameObjectName) {
        Container_Base obj = Container_Base.Cast(GetGame().CreateObject(gameObjectName, position));
        if (!obj) {
            return false;
        }

        obj.SetFlags(EntityFlags.STATIC, false);
        DZLSpawnHelper.SetPositionAndOrientation(obj, position, orientation);

		return true;
    }

    static PlayerBase SpawnBankingPoint(vector pos, vector orientation, string gameObjectName) {
        pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
        Object game_obj = GetGame().CreateObject(gameObjectName, pos, false, false, true );
        if (!game_obj) {
           return null;
        }

        PlayerBase bankChar = PlayerBase.Cast(game_obj);

        bankChar.SetAllowDamage(false);
        DZLSpawnHelper.SetPositionAndOrientation(bankChar, pos, orientation);
        bankChar.IsDZLBank = true;

        return bankChar;
    }

    static void SetPositionAndOrientation(Entity game_obj, vector position, vector orientation) {
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