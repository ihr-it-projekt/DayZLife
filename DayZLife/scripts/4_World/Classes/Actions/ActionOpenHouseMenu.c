class ActionOpenHouseMenu: ActionInteractBase
{
	void ActionOpenHouseMenu()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_HUDCursorIcon = CursorIcons.CloseHood;
	}

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTCursor;
    }

	override string GetText()
	{
		return "#open_house_menu";
	}

	override void OnStartClient(ActionData action_data)
	{
		super.OnStartClient(action_data);

		if (g_Game.GetUIManager().GetMenu() == NULL){
            PlayerBase player = PlayerBaseHelper.GetPlayer();
			
			if(!action_data) return;
            if(!action_data.m_Target) return;
            if(!IsBuilding(action_data.m_Target)) return;
            if (!player.GetConfig()) return;
			
			Building building = Building.Cast(action_data.m_Target.GetObject());

            DZLHouseDefinition definition = player.FindHouseDefinition(building);
			if (definition) {
			    player.RequestUpdateDZLPlayer();
			    GetGame().GetUIManager().ShowScriptedMenu(player.GetHouseMenu(definition, building), NULL);
			}
        }
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if (GetGame().IsClient()){
            if(!target) return false;
            if(!IsBuilding(target)) return false;
            if (!player.GetConfig()) return false;


            Building _building = Building.Cast(target.GetObject());
            int doorIndex = _building.GetDoorIndex(target.GetComponentIndex());
            if (doorIndex == -1) return false;

            if(!IsInReach(player, target, UAMaxDistances.DEFAULT) ) return false;
            
            DZLHouseDefinition definition = player.FindHouseDefinition(Building.Cast(target.GetObject()));

            return !!definition;
        }

		if (GetGame().IsServer()) {
		    return true;
        }

		return false;
    }
}
