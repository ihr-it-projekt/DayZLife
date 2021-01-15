class ActionRobMoney: ActionInteractBase
{
    void ActionRobMoney() {
		m_CommandUID = DayZPlayerConstants.CMD_GESTUREFB_COME;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
    }

    override void CreateConditionComponents()
    {
        m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
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
        if (!EntityAI.Cast(target.GetObject()).IsPlayer()) return false;

        PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());

        return targetPlayer.IsRestrained() || targetPlayer.IsUnconscious();
    }

    override void OnEndServer(ActionData action_data) {
        PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
        PlayerBase player = action_data.m_Player;
        DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(player.GetIdentity().GetId());

        if (targetPlayer.IsRestrained() || targetPlayer.IsUnconscious()) {
            if (!targetPlayer && !targetPlayer.GetIdentity()) return;

            DZLPlayer dzlTargetPlayer = DZLDatabaseLayer.Get().GetPlayer(targetPlayer.GetIdentity().GetId());
            if (dzlTargetPlayer && dzlTargetPlayer.HasMoney()) {
                dzlTargetPlayer.TransferFromPlayerToOtherPlayer(dzlPlayer);

                GetGame().RPCSingleParam(player, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, new Param1<ref DZLPlayer>(null), true, player.GetIdentity());
                GetGame().RPCSingleParam(targetPlayer, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, new Param1<ref DZLPlayer>(null), true, targetPlayer.GetIdentity());
            }
        }
    }
}
