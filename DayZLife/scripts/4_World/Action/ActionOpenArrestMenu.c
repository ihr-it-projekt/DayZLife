class ActionOpenArrestMenu: ActionInteractBase
{
    void ActionOpenArrestMenu() {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
    }

    override void CreateConditionComponents() {
        m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
        m_ConditionItem = new CCINone;
    }

    override string GetText() {
        return "#give_arrest";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
		if (!target.GetObject()) return false;
        if (!EntityAI.Cast(target.GetObject()).IsPlayer()) return false;
		
		PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());
		
		if (!targetPlayer.IsDZLPlayer()) return false;
		
		DZLPlayer dzlPlayerCop;
        if (GetGame().IsServer()) {
            dzlPlayerCop = DZLDatabaseLayer.Get().GetPlayer(player.GetIdentity().GetId());
            DZLPlayer dzlPlayerPrisoner = DZLDatabaseLayer.Get().GetPlayer(targetPlayer.GetIdentity().GetId());
            if (dzlPlayerPrisoner.IsActiveAsCop()) return false;
        } else {
			dzlPlayerCop = player.dzlPlayer;
		}

        if (!dzlPlayerCop.IsActiveAsCop()) return false;
		
        return true;
    }

    override void OnStartClient(ActionData action_data) {
        PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
        PlayerBase player = action_data.m_Player;
        DZLPlayerArrestMenu menu = player.GetArrestMenu();
		menu.SetReceiver(targetPlayer);
		GetGame().GetUIManager().ShowScriptedMenu(menu, NULL);
    }
}
