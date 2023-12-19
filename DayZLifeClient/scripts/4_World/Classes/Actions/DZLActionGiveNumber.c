class DZLActionGiveNumber: ActionInteractBase {
    void ActionRobMoney() {
        m_CommandUID = DayZPlayerConstants.CMD_GESTUREFB_COME;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
    }

    override void CreateConditionComponents() {
        m_ConditionTarget = new CCTMan;
        m_ConditionItem = new CCINone;
    }

    override string GetText() {
        return "#send_contact";
    }

    override void OnEndServer(ActionData action_data) {
        PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
        PlayerBase player = action_data.m_Player;
        DZLPlayer dzlPlayer = player.GetDZLPlayer();

        if (!targetPlayer && !targetPlayer.GetDZLPlayer()) return;

        DZLPlayer dzlTargetPlayer = targetPlayer.GetDZLPlayer();

        if (dzlTargetPlayer) {
            DZLSendMessage(player.GetIdentity(), "#contact_was_send");
            DZLSendMessage(targetPlayer.GetIdentity(), "#got_new_contact");

            DZLOnlinePlayer onlinePlayer = new DZLOnlinePlayer(player.GetIdentity().GetId(), player.GetIdentity().GetName(), DZLDatabaseLayer.Get().GetPlayer(player.GetIdentity().GetId()).GetJobGrade());

            GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_SEND_CONTACT, new Param1<ref DZLOnlinePlayer>(onlinePlayer), true, targetPlayer.GetIdentity());
        }
    }
}
