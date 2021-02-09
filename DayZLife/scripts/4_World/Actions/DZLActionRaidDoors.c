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

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
	    if (GetGame().IsClient() && (!player.config || !player.config.houseConfig || !player.GetDZLPlayer())) return false;

		if(GetGame().IsClient()){
			config = player.config.houseConfig;
		} else {
		    if (!DZLLicenceCheck.Get().HasActiveLicence(player.GetIdentity())) return false;
		}

		Building building = Building.Cast(target.GetObject());

		if (!building) return false;

		if(building.IsBuilding()) {
		    item = player.GetItemInHands();
            if (!item) return false;

			DZLJobHouseDefinition copHouseDefinition = config.GetCopHouseDefinition(building);
			DZLJobHouseDefinition medicDefinition;
			DZLHouseDefinition definition;

			array<string> raidTools = new array<string>;
			
            if(copHouseDefinition && player.GetDZLPlayer().IsActiveAsCop()) {
                return false;
            } else if (copHouseDefinition && !player.GetDZLPlayer().IsActiveAsCop()) {
                raidTools = copHouseDefinition.raidTools;
            } else {
                medicDefinition = config.GetMedicHouseDefinition(building);
                if(medicDefinition && player.GetDZLPlayer().IsActiveAsMedic()) {
                    return false;
                } else if (medicDefinition && !player.GetDZLPlayer().IsActiveAsMedic()) {
                    raidTools = medicDefinition.raidTools;
                } else {
                     definition = config.GetHouseDefinitionByBuilding(building);
                     if (!definition) return false;
                     raidTools = definition.raidTools;
                }
            }

			foreach(string itemType: raidTools) {
				if (item.GetType() == itemType) {
					if (GetGame().IsServer() && item.GetHealth() < 50) {
						DZLSendMessage(player.GetIdentity(), "#raid_item_has_not_enough_helth");
					    
                        return false;
					}

					int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
					if (doorIndex != -1 && !building.IsDoorOpen(doorIndex)) {
					    if (copHouseDefinition) return true;
					    if (medicDefinition) return true;

						if (GetGame().IsServer()) {
							DZLHouse dzlHouse = DZLDatabaseLayer.Get().GetHouse(building);
							if(dzlHouse && definition && dzlHouse.CanRaidDoor(player, doorIndex)) return true;

                            DZLSendMessage(player.GetIdentity(), "#you_can_not_raid_that_door");
                            return false;
						}
						
						return !building.IsDoorOpen(doorIndex);
					}
				}
			}
		}
		
		return false;
	}

	override void OnEndClient(ActionData action_data) {
	    if (g_Game.GetUIManager().GetMenu() != NULL) return;
		Building buildingClient = Building.Cast(action_data.m_Target.GetObject());
		DZLDoorRaidProgressBar bar = action_data.m_Player.GetRaidProgressBar();
		
		int doorIndex = buildingClient.GetDoorIndex(action_data.m_Target.GetComponentIndex());
		if (doorIndex != -1) {
			bar.SetBuilding(buildingClient, doorIndex);
						
			bar.SetRaidItem(action_data.m_MainItem);
			GetGame().RPCSingleParam(action_data.m_Player, DAY_Z_LIFE_GET_DZL_BUILDING_RAID_DOOR, new Param1<Building>(buildingClient), true);
			GetGame().GetUIManager().ShowScriptedMenu(bar, NULL);
			
		}
	}
	

};
