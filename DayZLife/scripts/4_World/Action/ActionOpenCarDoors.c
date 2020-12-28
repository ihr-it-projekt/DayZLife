modded class ActionOpenCarDoors
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item )
	{
        CarScript carScript = CarScript.Cast(target.GetParent());
        if (carScript && GetGame().IsServer()) {
            if (carScript.HasPlayerAccess(player.GetIdentity().GetId())) {
                return super.ActionCondition(player, target, item);
            }
            return false;
        }
		
		return super.ActionCondition(player, target, item);
	}
};
