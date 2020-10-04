
modded class ActionOpenDoors: ActionInteractBase
{

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(GetGame().IsClient()){
		    DebugMessageServerDZL("Try open Door client");
			return super.ActionCondition(player, target, item);
		}

		DebugMessageServerDZL("Try open Door22");
		if(super.ActionCondition(player, target, item)){
			DZLBuilding building = DZLBuildingHelper.ActionTargetToDZLBuilding(target);
			if(building && (building.HasOwner() && building.IsOwner(player))){

				return true;
			} else if (building && !building.HasOwner()) {
                return false;
			}
		}
		return false;
	}

};