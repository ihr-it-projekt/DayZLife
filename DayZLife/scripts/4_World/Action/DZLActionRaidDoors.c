class DZLActionRaidDoors: ActionInteractBase
{
	void DZLActionRaidDoors() {
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
        m_HUDCursorIcon = CursorIcons.CloseDoors;
	}

	override string GetText(){
		return "#break_door";
	}
	
	override void CreateConditionComponents()
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTCursor;
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
			DZLHouseDefinition definition = player.config.houseConfig.GetHouseDefinitionByBuilding(building);
		   
			foreach(string itemType: definition.raidTools) {
				if (item.GetType() == itemType) {
					if (GetGame().IsServer()) {
						if (item.GetHealth() < 50) {
							return false;
						}
					}
					int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
					if (doorIndex != -1) {
						return !building.IsDoorOpen(doorIndex) && building.IsDoorLocked(doorIndex);
					}
				}
			}
		}
		
		return false;
	}

	override void OnStartClient(ActionData action_data) {
		super.OnStartClient(action_data);
		Building buildingClient = Building.Cast(action_data.m_Target.GetObject());
		DZLDoorRaidProgressBar bar = action_data.m_Player.GetRaidProgressBar();
		
		int doorIndex = buildingClient.GetDoorIndex(action_data.m_Target.GetComponentIndex());
		if (doorIndex != -1) {
			bar.SetBuilding(buildingClient, doorIndex);
			DZLHouseDefinition definition = action_data.m_Player.config.houseConfig.GetHouseDefinitionByBuilding(buildingClient);
			
			if (definition) {
				bar.SetMaxRange(definition.raidRange);
				bar.SetRaidItem(action_data.m_MainItem);
				GetGame().RPCSingleParam(action_data.m_Player, DAY_Z_LIFE_GET_DZL_BUILDING_RAID_DOOR, new Param2<PlayerBase, Building>(action_data.m_Player, buildingClient), true);
				GetGame().GetUIManager().ShowScriptedMenu(bar, NULL);
			}
		}
	}
	

};