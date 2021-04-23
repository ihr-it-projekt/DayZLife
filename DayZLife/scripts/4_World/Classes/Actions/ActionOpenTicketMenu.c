class ActionOpenTicketMenu: ActionInteractBase
{
    void ActionOpenTicketMenu() {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
    }

    override void CreateConditionComponents() {

        if (DAY_Z_LIFE_DEBUG) {
            m_ConditionTarget = new DZL_CCTCar(true);
        } else {
            m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
        }
        m_ConditionItem = new CCINone;
    }

    override string GetText() {
        return "#give_a_ticket";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if (DAY_Z_LIFE_DEBUG) return true;

		if (!target.GetObject()) return false;
        if (!EntityAI.Cast(target.GetObject()).IsPlayer()) return false;
        DZLPlayer dzlPlayerCop = player.GetDZLPlayer();
        if (!dzlPlayerCop.IsActiveAsCop()) return false;
		
		PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());
		if (!targetPlayer.IsDZLPlayer()) return false;

        if (GetGame().IsServer()) {
            if(!targetPlayer || !targetPlayer.GetIdentity()) return false;

            DZLPlayer dzlPlayerPrisoner = targetPlayer.GetDZLPlayer();
            if (dzlPlayerPrisoner.IsActiveAsCop()) return false;
        }

        return true;
    }

    override void OnStartClient(ActionData action_data) {
        if (g_Game.GetUIManager().GetMenu() != NULL) return;
        PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
        PlayerBase player = action_data.m_Player;
        DZLPlayerTicketMenu menu = player.GetTicketMenu();
		menu.SetReceiver(targetPlayer);

		if (DAY_Z_LIFE_DEBUG) {
		    menu.SetReceiver(player);
		}

		GetGame().GetUIManager().ShowScriptedMenu(menu, NULL);
    }
}
