class ActionOpenLicenseMenu: ActionInteractBase
{
	void ActionOpenLicenseMenu()
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
		return "#open_licence_menu";
	}

	override void OnStartClient(ActionData action_data) {
		super.OnStartClient(action_data);

		if (g_Game.GetUIManager().GetMenu() == NULL){
            PlayerBase player = PlayerBaseHelper.GetPlayer();
			
			if(!action_data) return;
            if(!action_data.m_Target) return;
            if(!action_data.m_Target.GetObject()) return;
            if(!action_data.m_Target.GetObject().IsMan()) return;
           	if (!PlayerBase.Cast(action_data.m_Target.GetObject()).IsLicencePoint) return;
			
			GetGame().GetUIManager().ShowScriptedMenu(player.GetLicenceMenu(), NULL);
        }
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
	    if (GetGame().IsServer()) return true;

        if(!target.GetObject()) return false;

        PlayerBase npc = PlayerBase.Cast(target.GetObject());

        if (!npc) return false;

        return npc.IsLicencePoint;
	}
}