class DZLActionLockDoors: ActionInteractBase
{
	void DZLActionLockDoors() {
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_HUDCursorIcon = CursorIcons.OpenDoors;
	}
	
	override void CreateConditionComponents(){
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTCursor;
	}
	
	override string GetText() {
        return "#lock_door";
    }

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item )
	{
		DZLPlayerHouse house;
		if(GetGame().IsClient()){
			house = player.house;
			
		} else {
			house = new DZLPlayerHouse(player.GetIdentity());
		}
		
		if (!house) {
			return false;
		}

		Building building = Building.Cast(target.GetObject());

		if (!building) return false;

		if(building.IsBuilding() && house.HasHouse(building)) {
			int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
			if (doorIndex != -1) {
				if (GetGame().IsServer()) {
					DZLHouse dzlHouse = DZLBuildingHelper.ActionTargetToDZLHouse(target);

					if (dzlHouse && dzlHouse.CanLookDoor(player, doorIndex) && !building.IsDoorOpen(doorIndex)) {
					    return true;
					} else {
					    DZLSendMessage(player.GetIdentity(), "#can_not_look_door");
					}
				} else {
					return !building.IsDoorOpen(doorIndex);
				}
			}
		}
		return false;
	}

	override void OnEndServer(ActionData action_data) {
		Building building = Building.Cast(action_data.m_Target.GetObject());
		int doorIndex = building.GetDoorIndex(action_data.m_Target.GetComponentIndex());
		DZLHouse dzlHouse = DZLBuildingHelper.ActionTargetToDZLHouse(action_data.m_Target);
		if (dzlHouse && doorIndex != -1) {
			dzlHouse.LockDoor(doorIndex);
		}
	}

};