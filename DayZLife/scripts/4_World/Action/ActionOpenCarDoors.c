modded class ActionOpenCarDoors
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item )
	{
        CarScript carScript = CarScript.Cast(target.GetParent());
        if ((player && player.dzlPlayer && player.dzlPlayer.IsActiveAsCop()) || (carScript && carScript.HasPlayerAccess(player.GetIdentity().GetId())) || (player && player.IsInVehicle())) {
            return super.ActionCondition(player, target, item);
        } else if (carScript) {
            return false;
        }
		
		return super.ActionCondition(player, target, item);
	}
};
