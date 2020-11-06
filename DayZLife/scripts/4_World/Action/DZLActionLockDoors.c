class DZLActionLockDoors: ActionInteractBase
{
	ref DZLPlayerHouse house;
	
	override string GetText() {
        return "#lock_door";
    }

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(GetGame().IsClient()){
			house = player.house;
		} else {
			house = new DZLPlayerHouse(player);
		}

		if(super.ActionCondition(player, target, item)){
			Building building = Building.Cast(target.GetObject());
			if(building.IsBuilding() && house.HasHouse(building)) {
				if (GetGame().IsServer()) {
					DZLBuilding dzlBuilding = DZLBuildingHelper.ActionTargetToDZLBuilding(target);
	
					if(dzlBuilding && (dzlBuilding.HasOwner() && dzlBuilding.IsOwner(player))){
						return !building.IsDoorLocked(target.GetComponentIndex());
					} 
				
				} else {
					return !building.IsDoorLocked(target.GetComponentIndex());;
				}
			} 
		}
		return false;
	}
	
	override void OnEndServer(ActionData action_data) {
		Building building = Building.Cast(action_data.m_Target.GetObject());
		building.LockDoor(action_data.m_Target.GetComponentIndex());
	}

};