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
			if(!action_data.m_Target) return;
	        if(!action_data.m_Target.GetObject()) return;
	        TBLOLoadoutActionObject objectTarget = TBLOLoadoutActionObject.Cast(action_data.m_Target.GetObject());
	        if (!objectTarget) return;
			
			vector pos = objectTarget.GetPosition();
			
			TBLOConfig config = TBLOPlayerClientDB.Get().GetConfig();
			TBLOLoadOutPosition currentPos = null;
			foreach(TBLOLoadOutPosition possition: config.loadOuts.loadOutPosition) {
				if (possition.IsLoadOut(pos)) {
					currentPos = possition;
					break;
				}
			}
			
			if (!currentPos) return;
			
		
		    TBLOLoadOutMenu menu = action_data.m_Player.GetLoadOutMenu();
			
			
            if (config.loadOuts && config.loadOuts.loadOutCategories) {
				
				bool hasFoundOneCat = false;
				foreach(TBLOLoadOutCategory cat: config.loadOuts.loadOutCategories) {
					if (currentPos.HasCategory(cat.name)) {
						menu.AddCategory(cat);
						hasFoundOneCat = true;
					}
				}

				if (hasFoundOneCat) {
					GetGame().GetUIManager().ShowScriptedMenu(menu, NULL);
				}
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
