class ActionRobMoneyFromDead: ActionInteractBase
{
    void ActionRobMoney() {
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
    }

    override void CreateConditionComponents()
    {
        m_ConditionTarget = new CCTNone;
        m_ConditionItem = new CCINone;
    }

    override string GetText()
    {
        return "#rob_money";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if (GetGame().IsServer()) {
            if (!DZLLicenceCheck.Get().HasActiveLicence(player.GetIdentity())) return false;
        }
        if (!target.GetObject()) return false;
        EntityAI targetEntity = EntityAI.Cast(target.GetObject());

        if (!targetEntity || !targetEntity.IsPlayer()) return false;

		PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());

        return !targetPlayer.IsAlive() && targetPlayer.GetMoneyPlayerIsDead() > 0;
    }

    override void OnEndServer(ActionData action_data) {
        PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
        PlayerBase player = action_data.m_Player;
        DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(player.GetIdentity().GetId());

        if (!targetPlayer.IsAlive() && targetPlayer.GetMoneyPlayerIsDead() > 0) {
            targetPlayer.TransferFromDeadPlayer(dzlPlayer);

            GetGame().RPCSingleParam(player, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, new Param1<ref DZLPlayer>(null), true, player.GetIdentity());
        }
    }

    override void OnEndClient(ActionData action_data) {
        PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
        targetPlayer.SetMoneyPlayerIsDead(0);
    }
}
