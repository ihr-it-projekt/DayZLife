class DZLActionRaidDoors: ActionInteractBase
{
    ref DZLHouseConfig config;

	void DZLActionRaidDoors(){
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
        m_HUDCursorIcon = CursorIcons.OpenDoors;

        if (GetGame().IsServer()){
            config = DZLConfig.Get().houseConfig;
        }
	}

	override string GetText(){
		return "#break_door";
	}
	
	override void CreateConditionComponents(){	
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTCursor;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item){
	    if (GetGame().IsClient() && (!player.config || !player.config.houseConfig)) return false;

		if(GetGame().IsClient()){
			config = player.config.houseConfig;
		}

		Building building = Building.Cast(target.GetObject());

		if (!building) return false;

		if(building.IsBuilding()) {
			DZLCopHouseDefinition copHouseDefinition = config.GetCopHouseDefinition(building);
			array<string> raidTools = new array<string>;
			
			if (copHouseDefinition) {
				raidTools = copHouseDefinition.raidTools;
				
				if (GetGame().IsServer()) {
					if(DZLDatabaseLayer.Get().GetPlayer(player.GetIdentity().GetId()).IsActiveAsCop()) {
						DZLSendMessage(player.GetIdentity(), "#active_cops_can_not_raid_police_buildings");
						return false;
					}
				}
				
			} else {
				DZLHouseDefinition definition = config.GetHouseDefinitionByBuilding(building);
				if (!definition) return false;
				
				raidTools = definition.raidTools;
			}
						
			item = player.GetItemInHands();

			if (!item) return false;
						
		   
			foreach(string itemType: raidTools) {
				if (item.GetType() == itemType) {
					if (GetGame().IsServer() && item.GetHealth() < 50) {
						DZLSendMessage(player.GetIdentity(), "#raid_item_has_not_enough_helth");
					    
                        return false;
					}

					int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
					if (doorIndex != -1) {
						if (GetGame().IsServer()) {
							DZLHouse dzlHouse = DZLDatabaseLayer.Get().GetHouse(building);
							if (!building.IsDoorOpen(doorIndex) && dzlHouse && (copHouseDefinition || dzlHouse.CanRaidDoor(player, doorIndex))) {
								return true;
							} else {
							    DZLSendMessage(player.GetIdentity(), "#you_can_not_raid_that_door");
							    return false;
							}
						}
						
						return !building.IsDoorOpen(doorIndex);
					}
				}
			}
		}
		
		return false;
	}

	override void OnEndClient(ActionData action_data) {
		Building buildingClient = Building.Cast(action_data.m_Target.GetObject());
		DZLDoorRaidProgressBar bar = action_data.m_Player.GetRaidProgressBar();
		
		int doorIndex = buildingClient.GetDoorIndex(action_data.m_Target.GetComponentIndex());
		if (doorIndex != -1) {
			bar.SetBuilding(buildingClient, doorIndex);
			
			DZLCopHouseDefinition copHouseDefinition = config.GetCopHouseDefinition(buildingClient);
			int raidRange = 0;
			
			if (copHouseDefinition) {
				raidRange = copHouseDefinition.raidRange;
			} else {
				DZLHouseDefinition definition = config.GetHouseDefinitionByBuilding(buildingClient);
				if (!definition) return;
				
				raidRange = definition.raidRange;
			}
			
			
			bar.SetMaxRange(raidRange);
			bar.SetRaidItem(action_data.m_MainItem);
			GetGame().RPCSingleParam(action_data.m_Player, DAY_Z_LIFE_GET_DZL_BUILDING_RAID_DOOR, new Param2<PlayerBase, Building>(action_data.m_Player, buildingClient), true);
			GetGame().GetUIManager().ShowScriptedMenu(bar, NULL);
			
		}
	}
	

};
