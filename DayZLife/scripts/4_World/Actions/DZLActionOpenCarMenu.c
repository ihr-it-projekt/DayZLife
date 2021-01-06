class DZLActionOpenCarMenu: ActionInteractBase
{
	void ActionOpenCarMenu()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_HUDCursorIcon = CursorIcons.CloseHood;
	}

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTCursor;
    }

	override string GetText() {
		return "#open_car_menu";
	}
	
	override void OnStartClient(ActionData action_data)
	{
		if (g_Game.GetUIManager().GetMenu() == NULL){
		    PlayerBase player = action_data.m_Player;
            CarScript car = CarScript.Cast(action_data.m_Target.GetParent());

			
			if (car) {
				GetGame().GetUIManager().ShowScriptedMenu(player.GetCarMenu(car), NULL);
			}
        }
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if (!GetGame().IsServer() && g_Game.GetUIManager().GetMenu() != NULL){
			return false;
		}
        CarScript car = CarScript.Cast(target.GetParent());

		if (car) {
            return car.IsOwner(player.GetIdentity());
		}

		return false;
    }
}
