class ActionOpenUpgradeHouseMenu: ActionInteractBase
{
	void ActionOpenUpgradeHouseMenu()
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
		return "#open_house_upgrade_menu";
	}

	override void OnStartClient(ActionData action_data)
	{
		super.OnStartClient(action_data);

		if (g_Game.GetUIManager().GetMenu() == NULL){
            PlayerBase player = PlayerBaseHelper.GetPlayer();
			
			if(!action_data) return;
            if(!action_data.m_Target) return;
            if(!IsBuilding(action_data.m_Target)) return;
            if (!player.config) return;
            if (!player.house) return;
			
			Building building = Building.Cast(action_data.m_Target.GetObject());

            DZLHouseDefinition definition = player.FindHouseDefinition(building);
			
			if (definition) GetGame().GetUIManager().ShowScriptedMenu(player.GetHouseUpgradeMenu(definition, building), NULL);
        }
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if (GetGame().IsClient()) {
            if (!player.house) return false;
            if(!IsBuilding(target)) return false;

            Building _building = Building.Cast(target.GetObject());
            int doorIndex = _building.GetDoorIndex(target.GetComponentIndex());
            if (doorIndex == -1) return false;

            if(!IsInReach(player, target, UAMaxDistances.DEFAULT) ) return false;

            return player.house.HasHouse(Building.Cast(target.GetObject()));
        }

        return true;
	}
}
