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
            CarScript car;
            if (player && player.GetCommand_Vehicle()){
                car = CarScript.Cast(player.GetCommand_Vehicle().GetTransport());
            } else {
                car = CarScript.Cast(action_data.m_Target.GetParent());
            }
			
			if (car) {
				GetGame().GetUIManager().ShowScriptedMenu(player.GetCarMenu(car), NULL);
			}
        }
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if (!GetGame().IsServer() && g_Game.GetUIManager().GetMenu() != NULL){
			return false;
		}
        CarScript car;
        if (player && player.GetCommand_Vehicle()){
            car = CarScript.Cast(player.GetCommand_Vehicle().GetTransport());
        } else {
            car = CarScript.Cast(target.GetParent());
        }

        if (!car) {
            car = CarScript.Cast(target.GetObject());
        }

		if (car) {
		    if (GetGame().IsServer()) {
		        return car.IsOwner(player.GetIdentity());
		    }
			return true;
		}

		return false;
    }
}
