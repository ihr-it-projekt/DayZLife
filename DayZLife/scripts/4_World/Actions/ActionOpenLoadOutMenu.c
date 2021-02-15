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
		    DZLLoadOutMenu menu = action_data.m_Player.GetLoadOutMenu();
		    if (action_data.m_Player.GetDZLPlayer().IsActiveAsCop()) {
                menu.SetCategories(action_data.m_Player.config.jobConfig.loadOutsCops.loadOutCategories);
            } else if (action_data.m_Player.GetDZLPlayer().IsActiveAsMedic()) {
                menu.SetCategories(action_data.m_Player.config.jobConfig.loadOutsMedics.loadOutCategories);
            }

			GetGame().GetUIManager().ShowScriptedMenu(menu, NULL);
        }
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
		if (GetGame().IsServer()) return DZLLicenceCheck.Get().HasActiveLicence(player.GetIdentity());

		DZLBaseActionObject objectTarget = DZLBaseActionObject.Cast(target.GetObject());
        if (!objectTarget || !objectTarget.IsLoadOut()) return false;

	    DZLPlayer dzlPlayer = player.GetDZLPlayer();
	    if (!dzlPlayer || !player.config || !player.config.jobConfig) return false;

        if (dzlPlayer.IsActiveAsCop()) {
            return objectTarget.IsCopLoadOut();
        } else if (dzlPlayer.IsActiveAsMedic()) {
            return objectTarget.IsMedicLoadOut();
        }
		
		return false;
	}
}
