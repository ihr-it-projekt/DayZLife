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
	    if (GetGame().IsServer()) return DZLLicenceCheck.Get().HasActiveLicence(player.GetIdentity());

        if(!target.GetObject()) return false;

        PlayerBase npc = PlayerBase.Cast(target.GetObject());

        if (!npc) return false;

        if (npc.IsDZLBank) {
            DZLDate currentDate = new DZLDate();

            if(!player.hasBankingConfig && currentDate.inSeconds - player.timeAskForBankingConfig > 5) {
                player.timeAskForBankingConfig = currentDate.inSeconds;
                GetGame().RPCSingleParam(player, DAY_Z_LIFE_EVENT_GET_CONFIG_BANKING, new Param1<ref PlayerBase>(player), true);
            }

            return player.hasBankingConfig;
        }

        return false;
	}
}
