modded class ActionOpenDoors
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(!target) return false;
		if(!IsBuilding(target)) return false;

		Building building = Building.Cast(target.GetObject());
		if(building) {
			int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
			if ( doorIndex != -1 ) {
			    if (GetGame().IsServer()) {
                    DZLHouse dzlHouse = DZLBuildingHelper.ActionTargetToDZLHouse(target);
                    return (dzlHouse && !dzlHouse.IsDoorLooked(doorIndex));
                }
				return (!building.IsDoorOpen(doorIndex) && !building.IsDoorLocked(doorIndex));
			}
		}
		return false;
	}

};