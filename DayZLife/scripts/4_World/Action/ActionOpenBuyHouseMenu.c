class ActionOpenBuyHouseMenu: ActionInteractBase
{
	void ActionOpenBuyHouseMenu()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
		m_HUDCursorIcon = CursorIcons.None;
	}

	override string GetText()
	{
		return "#open_buy_menu";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return true;
	}
	
	override void OnExecuteClient(ActionData action_data)
	{
		super.OnExecuteClient(action_data);
		
		if(!DLBuyHouseMenu.GetInstance().IsVisible())
		{
			UIManager uiManager = GetGame().GetUIManager();
			uiManager.CloseAll();
			uiManager.ShowScriptedMenu(DLBuyHouseMenu.GetInstance(), null);
		}
	}
}