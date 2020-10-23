class ActionRobMoney : ActionInteractBase
{
    void ActionRobMoney()
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

    override string GetText()
    {
        return "#rob_money";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
		if (!target.GetObject()) return false;
        if (!EntityAI.Cast(target.GetObject()).IsPlayer()) return false;

        PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());

        if (!targetPlayer.IsAlive() && targetPlayer.GetMoneyPlayerIsDead() > 0) {
            m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
            return true;
        } else if (targetPlayer.IsAlive() && targetPlayer.IsRestrained()) {
            m_CommandUID = DayZPlayerConstants.CMD_GESTUREFB_COME;
            return true;
        }

        return false;
    }

    override void OnEndServer(ActionData action_data) {
        PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
        PlayerBase player = action_data.m_Player;
        DZLPlayer dzlPlayer = new DZLPlayer(player.GetIdentity().GetId());

        if (!targetPlayer.IsAlive() && targetPlayer.GetMoneyPlayerIsDead() > 0) {
            targetPlayer.TransferFromDeadPlayer(dzlPlayer);

            GetGame().RPCSingleParam(player, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(dzlPlayer), true, player.GetIdentity());
        } else if (targetPlayer.IsAlive() && targetPlayer.IsRestrained()) {
            DZLPlayer dzlTargetPlayer = new DZLPlayer(targetPlayer.GetIdentity().GetId());
            if (dzlTargetPlayer) {
                dzlTargetPlayer.TransferFromPlayerToOtherPlayer(dzlPlayer);

                GetGame().RPCSingleParam(player, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(dzlPlayer), true, player.GetIdentity());
                GetGame().RPCSingleParam(targetPlayer, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(dzlTargetPlayer), true, targetPlayer.GetIdentity());
            }
        }
    }

    override void OnEndClient(ActionData action_data) {
        PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
        targetPlayer.SetMoneyPlayerIsDead(0);
    }
}