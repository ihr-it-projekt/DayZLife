modded class ActionOpenCarDoors
{
    bool isSync = false;

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item )
	{
        CarScript carScript = CarScript.Cast(target.GetParent());
        if (carScript && GetGame().IsServer()) {
            if (carScript.HasPlayerAccess(player.GetIdentity().GetId())) {
                return super.ActionCondition(player, target, item);
            }
            return false;
        } else if (carScript && GetGame().IsClient() && carScript.dzlCarId == 0 && isSync == false) {
            GetGame().RPCSingleParam(carScript, DAY_Z_LIFE_UPDATE_CAR_FROM_PLAYER_SIDE, new Param1<CarScript>(carScript), true);
            DebugMessageDZL("sync car");
            isSync = true;
        }
		
		return super.ActionCondition(player, target, item);
	}
};
