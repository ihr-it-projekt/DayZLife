class ActionOpenBuyHouseMenu: ActionInteractBase
{
	void ActionOpenBuyHouseMenu()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_HUDCursorIcon = CursorIcons.CloseHood;
	}

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTNone;
    }

	override string GetText()
	{
		return "#open_house_buy_menu";
	}

	override void OnStartClient(ActionData action_data)
	{
		super.OnStartClient(action_data);

		if (g_Game.GetUIManager().GetMenu() == NULL){
			DebugMessageDZL("Action create Menu");
            PlayerBase player = PlayerBaseHelper.GetPlayer();
			
			if(!action_data) return;
            if(!action_data.m_Target) return;
            if(!IsBuilding(action_data.m_Target)) return;
            if (!player.config) return;
			
			Building building = Building.Cast(action_data.m_Target.GetObject());

            DZLHouseDefinition definition = player.FindHouseDefinition(building);
			if (definition) GetGame().GetUIManager().ShowScriptedMenu(player.GetHouseBuyMenu(definition, building), NULL);
        }
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if(GetGame().IsClient()){
            if(!target) return false;
            if(!IsBuilding(target)) return false;
            if (!player.config) return false;

            DZLHouseDefinition definition = player.FindHouseDefinition(Building.Cast(target.GetObject()));

            return !!definition;
        }

		if (GetGame().IsServer()) {
            DZLBuilding building = DZLBuildingHelper.ActionTargetToDZLBuilding(target);

            if (building && (!building.HasOwner() || (building.HasOwner() && building.IsOwner(player)))) {
                return true;
            }
        }

		return false;
    }
}