class DZLActionUnLockDoors: ActionInteractBase
{
	void DZLActionLockDoors() {
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
        m_HUDCursorIcon = CursorIcons.CloseDoors;
	}
	
	override void CreateConditionComponents(){
		m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTCursor;
	}
	
	override string GetText(){
		return "#unlock";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item )
	{
	    DZLPlayerHouse house;
		if(GetGame().IsClient()){
			house = player.house;
		} else {
			house = new DZLPlayerHouse(player);
		}

        if (!house) {
            return false;
        }

		Building building = Building.Cast(target.GetObject());

		if (!building) return false;

		if(building.IsBuilding() && house.HasHouse(building)) {
			int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
			if ( doorIndex != -1 ) {	
				if (GetGame().IsServer()) {
					DZLBuilding dzlBuilding = DZLBuildingHelper.ActionTargetToDZLBuilding(target);
					if(dzlBuilding && ((dzlBuilding.HasOwner() && dzlBuilding.IsOwner(player)) || !dzlBuilding.HasOwner())){
						return !building.IsDoorOpen(doorIndex) && building.IsDoorLocked(doorIndex);
					} 
				
				} else {
					return !building.IsDoorOpen(doorIndex) && building.IsDoorLocked(doorIndex);;
				}
			}
		} 
		return false;
	}
	
	override void OnEndServer(ActionData action_data) {
		Building building = Building.Cast(action_data.m_Target.GetObject());
		int doorIndex = building.GetDoorIndex(action_data.m_Target.GetComponentIndex());
		if ( doorIndex != -1 ) {
			building.UnlockDoor(doorIndex);
		}
	}

};