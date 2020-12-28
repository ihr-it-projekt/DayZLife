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
		super.OnStartClient(action_data);

		if (g_Game.GetUIManager().GetMenu() == NULL){
            PlayerBase player = PlayerBaseHelper.GetPlayer();
			
			if(!action_data) return;
            if(!action_data.m_Target) return;
            if(!IsTransport(action_data.m_Target)) return;
			
			CarScript car = CarScript.Cast(action_data.m_Target.GetParent());
			
			if (car && player.dzlPlayer.IsCarOwner(car.dzlCarId)) {
				GetGame().GetUIManager().ShowScriptedMenu(player.GetCarMenu(car), NULL);
			}
        }
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if (g_Game.GetUIManager().GetMenu() == NULL){
            if(!IsTransport(target)) return false;
			
			CarScript car = CarScript.Cast(target.GetParent());
			
			if (car && player.dzlPlayer.IsCarOwner(car.dzlCarId)) {
				return true;
			}
        }

		return false;
    }
}
