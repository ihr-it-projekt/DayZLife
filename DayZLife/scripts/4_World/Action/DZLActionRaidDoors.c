class DZLActionRaidDoors: ActionInteractBase
{
	ref DZLDoorRaidProgressBar bar;
	Building buildingClient;
	EntityAI usedItem;

	void DZLActionRaidDoors() {
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
        m_HUDCursorIcon = CursorIcons.CloseDoors;
		
		if (GetGame().IsClient()) {
            GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
		}
	}
	
	void ~DZLActionRaidDoors() {
		if (GetGame().IsClient()) {
            GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
		}
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
			if (!house) return false;
		} else {
			house = new DZLPlayerHouse(player);
		}
		Building building = Building.Cast(target.GetObject());
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
					if ( doorIndex != -1 ) {
						return !building.IsDoorOpen(doorIndex) && building.IsDoorLocked(doorIndex);
					}
				}
			}
		}
		
		return false;
	}

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
		if (rpc_type == DAY_Z_LIFE_GET_DZL_BUILDING_RAID_DOOR_RESPONSE) {
            autoptr Param1<DZLHouse> paramRaidDoorResponse;
            if (ctx.Read(paramRaidDoorResponse)){
                bar.SetDuration(paramRaidDoorResponse.param1.raidTime);
				bar.SetRaidItem(usedItem);
				
				GetGame().GetUIManager().ShowScriptedMenu(bar, NULL);
            }
        }
	}

	override void OnStartClient(ActionData action_data) {
		super.OnStartClient(action_data);
		buildingClient = Building.Cast(action_data.m_Target.GetObject());
		DZLDoorRaidProgressBar bar = action_data.m_Player.GetRaidProgressBar();
		
		int doorIndex = buildingClient.GetDoorIndex(action_data.m_Target.GetComponentIndex());
		if (doorIndex != -1) {
			bar.SetBuilding(buildingClient, doorIndex);
			DZLHouseDefinition definition = action_data.m_Player.config.houseConfig.GetHouseDefinitionByBuilding(buildingClient);
			
			if (definition) {
				bar.SetMaxRange(definition.raidRange);
				usedItem = action_data.m_MainItem;
				GetGame().RPCSingleParam(action_data.m_Player, DAY_Z_LIFE_GET_DZL_BUILDING_RAID_DOOR, new Param2<PlayerBase, Building>(action_data.m_Player, buildingClient), true);
			}
		}
	}
	

};