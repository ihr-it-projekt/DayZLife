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
	    Building building = Building.Cast(target.GetObject());
        if (!building || !building.IsBuilding()) return false;

	    if (!player.GetConfig() || !player.GetConfig().houseConfig || !player.GetDZLPlayer()) return false;

		config = player.GetConfig().houseConfig;
		
        item = player.GetItemInHands();
        if (!item) return false;

        if (GetGame().IsServer()) {
            if (DZLDatabaseLayer.Get().GetCopCount() < config.minCountOfCopsForRaid) return false;
        }



        DZLJobHouseDefinition definition = DZLCanDoDoorAction.GetJobHouseDefinition(building, player);

        array<string> raidTools = new array<string>;

        if(!definition) {
            #ifndef TBRealEstateClient
            DZLHouseDefinition houseDefinition = config.GetHouseDefinitionByBuilding(building);
			if (!houseDefinition) return false;
			
			raidTools = houseDefinition.raidTools;
			#endif
        } else {
            raidTools = definition.raidTools;
        }

        if (raidTools.Count() == 0) return false;

        foreach(string itemType: raidTools) {
            if (item.GetType() == itemType) {
                if (GetGame().IsServer() && item.GetHealth() < 50) {
                    DZLSendMessage(player.GetIdentity(), "#raid_item_has_not_enough_helth");

                    return false;
                }

                int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
                if (doorIndex != -1 && !building.IsDoorOpen(doorIndex)) {
                    if (GetGame().IsServer() && !definition) {
                        DZLHouse dzlHouse = DZLDatabaseLayer.Get().GetHouse(building);
                        if(dzlHouse && dzlHouse.CanRaidDoor(player, doorIndex)) return true;

                        DZLSendMessage(player.GetIdentity(), "#you_can_not_raid_that_door");
                        return false;
                    } else {
                        if (definition) return true;
                    }

                    return !building.IsDoorOpen(doorIndex);
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
