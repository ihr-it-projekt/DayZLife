class DZLActionRaidDoors: ActionInteractBase {

    void TBREActionRaidDoors() {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
        m_HUDCursorIcon = CursorIcons.OpenDoors;
    }

    override string GetText() {
        return "#tb_break_door";
    }

    override void CreateConditionComponents() {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTCursor;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
		BuildingBase building = BuildingBase.Cast(target.GetObject());
        if(!building) return false;
		
        if(!DZLCanDoDoorAction.IsJobDoor(building)) return false;
        if (DZLCanDoDoorAction.canDoByJob(building, player)) return false;

        int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
        if(doorIndex == -1) return false;

        if (!IsInReach(player, target, UAMaxDistances.DEFAULT)) return false;
        if (!building.IsDoorOpen(doorIndex)) return false;

        item = player.GetItemInHands();
        if(!item) return false;
		
		if (item.IsRuined()) return false;

        string type = item.GetType();

        DZLJobHouseDefinition definition = DZLCanDoDoorAction.GetJobHouseDefinition(building, player);
        if(!definition) return false;

        bool foundRaidTool = false;
        foreach(string jobRaidTool: definition.raidTools) {
            if(jobRaidTool != type) continue;
			
            foundRaidTool = true;
            break;
        }

        if(!foundRaidTool) return false;

        return true;
    }

    override void OnEndClient(ActionData action_data) {
        if(g_Game.GetUIManager().GetMenu() != NULL) return;
        BuildingBase buildingClient = BuildingBase.Cast(action_data.m_Target.GetObject());
        DZLDoorRaidProgressBar bar = action_data.m_Player.GetDZLRaidProgressBar();

        int doorIndex = buildingClient.GetDoorIndex(action_data.m_Target.GetComponentIndex());
        if(doorIndex == -1) return;
		
		DZLJobHouseDefinition definition = DZLCanDoDoorAction.GetJobHouseDefinition(buildingClient, action_data.m_Player);

        bar.SetBuilding(buildingClient, doorIndex, definition);
        GetGame().GetUIManager().ShowScriptedMenu(bar, NULL);
    }
};
