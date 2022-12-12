class TBLOActionOpenLoadOutMenu: ActionInteractBase
{
	void TBLOActionOpenLoadOutMenu()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
		m_HUDCursorIcon = CursorIcons.None;
	}

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new TBLO_CCTActionObject;
    }

	override string GetText() {
		return "#open_loadout_menu";
	}

	override void OnStartClient(ActionData action_data) {
		super.OnStartClient(action_data);

		if (g_Game.GetUIManager().GetMenu() == NULL){
		    TBLOLoadOutMenu menu = action_data.m_Player.GetLoadOutMenu();
			
			TBLOConfig config = TBLOPlayerClientDB.Get().GetConfig();
            if (config.loadOuts && config.loadOuts.loadOutCategories) {
                menu.SetCategories(config.loadOuts.loadOutCategories);
			    GetGame().GetUIManager().ShowScriptedMenu(menu, NULL);
            }
        }
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
		TBLOLoadoutActionObject objectTarget = TBLOLoadoutActionObject.Cast(target.GetObject());
        if (!objectTarget) return false;

        TBLOConfig config = TBLOPlayerClientDB.Get().GetConfig();

		return true;
	}
}
