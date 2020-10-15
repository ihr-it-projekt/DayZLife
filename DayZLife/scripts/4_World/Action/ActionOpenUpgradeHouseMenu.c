class ActionOpenUpgradeHouseMenu: ActionInteractBase
{
	void ActionOpenUpgradeHouseMenu()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
		m_HUDCursorIcon = CursorIcons.None;
	}

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTNone;
    }

	override string GetText()
	{
		return "#open_house_upgrade_menu";
	}

	override void OnStartClient(ActionData action_data)
	{
		super.OnStartClient(action_data);

		if (g_Game.GetUIManager().GetMenu() == NULL){
            PlayerBase player = GetGame().GetPlayer();
			
			if(!action_data) return;
            if(!action_data.m_Target) return;
            if(!IsBuilding(action_data.m_Target)) return;
            if (!player.config) return;

            DZLHouseDefinition definition;
			array<ref DZLHouseDefinition> houseConfigs = player.config.houseConfig.houseConfigs;
            foreach(DZLHouseDefinition _definition: houseConfigs) {
                if (_definition.houseType == action_data.m_Target.GetObject().GetType()) {
					definition = _definition;
					break;
                }
            }

			if (definition) GetGame().GetUIManager().ShowScriptedMenu(player.GetHouseUpgradeMenu(definition, action_data.m_Target.GetObject()), NULL);
        }
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if (GetGame().IsServer()) {
            DZLBuilding building = DZLBuildingHelper.ActionTargetToDZLBuilding(target);

            if (building && (building.IsOwner(player))) {
                return true;
            }
        }

		return super.ActionCondition(player, target, item);
    }
}