class TBMActionGiveNumber: ActionInteractBase
{
    void ActionRobMoney() {
		m_CommandUID = DayZPlayerConstants.CMD_GESTUREFB_COME;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
    }

    override void CreateConditionComponents()
    {
        m_ConditionTarget = new CCTMan;
        m_ConditionItem = new CCINone;
    }

    override string GetText()
    {
        return "#send_contact";
    }

    override void OnEndServer(ActionData action_data) {
        PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
        PlayerBase player = action_data.m_Player;

        if (!targetPlayer) return;

        TBMSendMessage(player.GetIdentity(), "#contact_was_send");
        TBMSendMessage(targetPlayer.GetIdentity(), "#got_new_contact");

        TBMOnlinePlayer onlinePlayer = new TBMOnlinePlayer(player.GetIdentity().GetId(), player.GetIdentity().GetName());

        GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_SEND_CONTACT, new Param1<ref TBMOnlinePlayer>(onlinePlayer), true, targetPlayer.GetIdentity());
        
    }
}
