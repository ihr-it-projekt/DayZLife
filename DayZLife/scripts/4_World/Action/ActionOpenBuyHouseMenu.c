class ActionOpenBuyHouseMenu: ActionInteractBase
{
	void ActionOpenBuyHouseMenu()
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
		return "#open_house_buy_menu";
	}

	override void OnStartClient(ActionData action_data)
	{
		super.OnStartClient(action_data);

		if ( g_Game.GetUIManager().GetMenu() == NULL ){
			DebugMessageDZL("Action create Menu");
            PlayerBase player = GetGame().GetPlayer();
		    GetGame().GetUIManager().ShowScriptedMenu(player.GetHouseBuyMenu(), NULL);
        }
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if(GetGame().IsClient()){
            if(!target) return false;
            if(!IsBuilding(target)) return false;

            bool hasFound = false;
            foreach(DZLHouseDefinition definition: player.config.houseConfig.houseConfigs) {
                if (definition.houseType == target.GetObject().GetType()) {
                    hasFound = true;
                    break;
                }
            }

            return hasFound;
        }

		if (GetGame().IsServer()) {
            DZLBuilding building = DZLBuildingHelper.ActionTargetToDZLBuilding(target);

            if (building && !building.HasOwner()) {
                return true;
            }
        }
		
		return false;
    }
}