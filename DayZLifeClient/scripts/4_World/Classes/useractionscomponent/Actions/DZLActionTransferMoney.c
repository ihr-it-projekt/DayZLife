class DZLActionTransferMoney: ActionInteractBase {
    void DZLActionTransferMoney() {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_HUDCursorIcon = CursorIcons.CloseHood;
    }

    override void CreateConditionComponents() {
        m_ConditionTarget = new CCTMan;
        m_ConditionItem = new CCINone;
    }

    override string GetText() {
        return "#transfer_money";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if(!target.GetObject()) return false;
        if(!EntityAI.Cast(target.GetObject()).IsPlayer()) return false;

        PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());
        if(!targetPlayer || !targetPlayer.IsDZLPlayer()) return false;

        return true;
    }

    override void OnStartClient(ActionData action_data) {
        if(g_Game.GetUIManager().GetMenu() != NULL) return;
        PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
        PlayerBase player = action_data.m_Player;

        DZLPlayerMoneyTransferMenu menu = player.GetPlayerMoneyTransferMenu();
        menu.SetReceiver(targetPlayer);
        g_Game.GetUIManager().ShowScriptedMenu(menu, NULL);
    }
}
