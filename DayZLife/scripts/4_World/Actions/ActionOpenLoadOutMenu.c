class ActionOpenLoadOutMenu: ActionInteractBase
{
	void ActionOpenLoadOutMenu()
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
		return "#open_loadout_menu";
	}

	override void OnStartClient(ActionData action_data) {
		super.OnStartClient(action_data);

		if (g_Game.GetUIManager().GetMenu() == NULL){		
			GetGame().GetUIManager().ShowScriptedMenu(action_data.m_Player.GetLoadOutMenu(), NULL);
        }
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
		if (GetGame().IsServer()) return DZLLicenceCheck.Get().HasActiveLicence(player.GetIdentity());
		
	    DZLPlayer dzlPlayer = player.GetDZLPlayer();
	    if (!dzlPlayer || !dzlPlayer.IsActiveAsCop()) return false;

        return player.config.jobConfig.loadOutsCops.IsInZone(player.GetPosition());
	}
}
