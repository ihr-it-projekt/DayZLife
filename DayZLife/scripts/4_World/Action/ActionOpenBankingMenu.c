class ActionOpenBankingMenu: ActionInteractBase
{
	void ActionOpenBankingMenu()
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

	override string GetText() {
		return "#open_banking_menu";
	}

	override void OnStartClient(ActionData action_data) {
		super.OnStartClient(action_data);

		if (g_Game.GetUIManager().GetMenu() == NULL){
            if(!action_data) return;
            if(!action_data.m_Target) return;
            if(!action_data.m_Target.GetObject()) return;
            if(!action_data.m_Target.GetObject().IsMan()) return;
           	if (!PlayerBase.Cast(action_data.m_Target.GetObject()).IsDZLBank) return;
			
			GetGame().GetUIManager().ShowScriptedMenu(action_data.m_Player.GetBankingMenu(), NULL);
        }
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
	    if (GetGame().IsServer()) return true;

        if(!target.GetObject()) return false;

        PlayerBase npc = PlayerBase.Cast(target.GetObject());

        if (!npc) return false;

        return npc.IsDZLBank;
	}
}