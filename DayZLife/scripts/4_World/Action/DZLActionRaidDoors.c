class DZLActionRaidDoors: ActionInteractBase
{
	ref DZLPlayerHouse house;
	ref DZLDoorRaidProgressBar bar;
	Building buildingClient;
	EntityAI usedItem;

	void DZLActionRaidDoors() {
		m_CallbackClass = ActionInteractBaseCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_PICKUP_HANDS;
		m_HUDCursorIcon = CursorIcons.Cursor;
		
		if (GetGame().IsClient()) {
            GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
		}
	}
	
	void ~DZLActionRaidDoors() {
		if (GetGame().IsClient()) {
            GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
		}
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
			    DZLHouseDefinition definition = player.config.houseConfig.GetHouseDefinitionByBuilding(building);
			   
				foreach(string itemType: definition.raidTools) {
					if (item.GetType() == itemType) {
						if (GetGame().IsServer()) {
							if (item.GetHealth() < 50) {
								return false;
							}
						} 
						return building.IsDoorLocked(target.GetComponentIndex());
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
		bar.SetBuilding(buildingClient, action_data.m_Target.GetComponentIndex());
		
		DZLHouseDefinition definition = action_data.m_Player.config.houseConfig.GetHouseDefinitionByBuilding(buildingClient);
		
		if (definition) {
			bar.SetMaxRange(definition.raidRange);
			usedItem = action_data.m_MainItem;
			
			GetGame().RPCSingleParam(action_data.m_Player, DAY_Z_LIFE_GET_DZL_BUILDING_RAID_DOOR, new Param2<PlayerBase, Building>(action_data.m_Player, buildingClient), true);
		}
	}
	

};