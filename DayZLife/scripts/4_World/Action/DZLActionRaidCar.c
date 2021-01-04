class DZLActionRaidCar: ActionInteractBase
{
    ref DZLCarConfig config;

	void DZLActionRaidCar(){
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
        m_HUDCursorIcon = CursorIcons.OpenDoors;

        if (GetGame().IsServer()){
            config = DZLConfig.Get().carConfig;
        }
	}

	override string GetText(){
		return "#break_door";
	}
	
	override void CreateConditionComponents(){	
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTCursor;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
	    if (GetGame().IsClient() && (!player.config || !player.config.carConfig)) return false;

		if(GetGame().IsClient()){
			config = player.config.carConfig;
		} else {
		    if (!DZLLicenceCheck.Get().HasActiveLicence(player.GetIdentity())) return false;
		}

		CarScript car = CarScript.Cast(target.GetParent());

		if (!car) return false;

        array<string> raidTools = config.carRaidTools;

        item = player.GetItemInHands();

        if (!item) return false;

        foreach(string itemType: raidTools) {
            if (item.GetType() == itemType) {
                if (GetGame().IsServer() && item.GetHealth() < 50) {
                    DZLSendMessage(player.GetIdentity(), "#raid_item_has_not_enough_helth");

                    return false;
                }
                return car.CanRaidDoor(player);
            }
        }

		return false;
	}

	override void OnEndClient(ActionData action_data) {
	    if (g_Game.GetUIManager().GetMenu() != NULL) return;
		CarScript car = CarScript.Cast(action_data.m_Target.GetParent());
		DZLCarRaidProgressBar bar = action_data.m_Player.GetRaidCarProgressBar();
		
		bar.SetCar(car);
		bar.SetMaxRange(2);

		EntityAI item = action_data.m_Player.GetItemInHands();
        if (!item) return;

		bar.SetRaidItem(item);
		bar.SetDuration(action_data.m_Player.config.carConfig.carRaidTimeInSeconds);
		GetGame().GetUIManager().ShowScriptedMenu(bar, NULL);
	
	}
	
};
