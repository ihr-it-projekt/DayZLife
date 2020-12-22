class DZLActionTransferMoney: ActionInteractBase
{
    void DZLActionTransferMoney() {
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_HUDCursorIcon = CursorIcons.CloseHood;
    }

    override void CreateConditionComponents() {
        m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
        m_ConditionItem = new CCINone;
    }

    override string GetText() {
        return "#transfer_money";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if (GetGame().IsServer()) {
            if (!DZLLicenceCheck.Get().HasActiveLicence(player.GetIdentity())) return false;
        }

		if (!target.GetObject()) return false;
        if (!EntityAI.Cast(target.GetObject()).IsPlayer()) return false;
		
		PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());
		
        if (!targetPlayer.IsDZLPlayer()) return false;

        return true;
    }

    override void OnStartClient(ActionData action_data) {
        PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
        PlayerBase player = action_data.m_Player;

        DZLPlayerMoneyTransferMenu menu = player.GetPlayerMoneyTransferMenu();
		menu.SetReceiver(targetPlayer);
		GetGame().GetUIManager().ShowScriptedMenu(menu, NULL);
    }
}
