modded class ActionOpenDoors: ActionInteractBase
{

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(GetGame().IsClient()){
			return super.ActionCondition(player, target, item);
		}

		if(super.ActionCondition(player, target, item)){
			DZLBuilding building = DZLBuildingHelper.ActionTargetToDZLBuilding(target);

			if(building && (building.HasOwner() && building.IsOwner(player))){
				return true;
			} else if (building && building.HasOwner() && !building.IsOwner(player)) {
                return false;
			} else if (building && !building.HasOwner()) {
                return true;
			}
		}
		return false;
	}

};