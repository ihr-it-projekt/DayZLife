class ActionOpenCarStorageMenu: ActionInteractBase
{
	void ActionOpenCarStorageMenu()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
		m_HUDCursorIcon = CursorIcons.None;
	}

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new DZL_CCTActionObject;
    }

	override string GetText() {
		return "#open_car_garage_menu";
	}

	override void OnStartClient(ActionData action_data) {
		super.OnStartClient(action_data);

		if (g_Game.GetUIManager().GetMenu() == NULL){		
			GetGame().GetUIManager().ShowScriptedMenu(action_data.m_Player.GetCarStorageMenu(), NULL);
        }
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
	    if (GetGame().IsServer()) return DZLLicenceCheck.Get().HasActiveLicence(player.GetIdentity());
        DZLBaseActionObject objectTarget = DZLBaseActionObject.Cast(target.GetObject());
        if (!objectTarget || !objectTarget.IsGarage()) return false;
        if (!player.GetConfig() || !player.GetConfig().carConfig) return false;

        return true;
	}
}
