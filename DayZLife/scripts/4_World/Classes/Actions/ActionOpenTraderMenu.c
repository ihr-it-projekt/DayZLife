class ActionOpenTraderMenu: ActionInteractBase
{
	void ActionOpenTraderMenu()
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
		return "#open_trader_menu";
	}

	override void OnStartClient(ActionData action_data) {
		super.OnStartClient(action_data);

		DZLTraderPosition position = action_data.m_Player.GetTraderByPosition();

		if (!position) return;

		if (!position.CanOpenWithJob(action_data.m_Player.GetDZLPlayer().GetActiveJob())) {
		    action_data.m_Player.DisplayMessage("#You_can_only_open_when_you_are_a: " + "#" + position.forJob);
		    return;
		}

		if (g_Game.GetUIManager().GetMenu() == NULL){
			GetGame().GetUIManager().ShowScriptedMenu(action_data.m_Player.GetTraderMenu(position), NULL);
        }
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        DZLBaseActionObject objectTarget = DZLBaseActionObject.Cast(target.GetObject());
        if (!objectTarget || !objectTarget.IsTrader()) return false;
       
		DZLDate currentDate = new DZLDate();
		
		if((!player.GetConfig() || !player.GetConfig().traderConfig)&& currentDate.inSeconds - player.timeAskForTraderConfig > 5) {
		    player.timeAskForTraderConfig = currentDate.inSeconds;
			GetGame().RPCSingleParam(player, DAY_Z_LIFE_EVENT_GET_CONFIG_TRADER, new Param1<PlayerBase>(player), true);
			GetGame().RPCSingleParam(player, DAY_Z_LIFE_EVENT_GET_CONFIG_TRADER_STORAGE, null, true);
			return false;
		}

		return true;
    }
}
