modded class DZLActionGiveNumber: ActionInteractBase {

    override void OnEndServer(ActionData action_data) {
        PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
        PlayerBase player = action_data.m_Player;
        DZLPlayer dzlPlayer = player.GetDZLPlayer();

        if(!targetPlayer && !targetPlayer.GetDZLPlayer() || !targetPlayer.GetIdentity()) return;

        DZLPlayer dzlTargetPlayer = targetPlayer.GetDZLPlayer();

        if(!dzlTargetPlayer) return;

        DZLSendMessage(player.GetIdentity(), "#contact_was_send");
        DZLSendMessage(targetPlayer.GetIdentity(), "#got_new_contact");

        DZLOnlinePlayer onlinePlayer = new DZLOnlinePlayer(player.GetIdentity().GetId(), player.GetIdentity().GetName(), DZLDatabaseLayer.Get().GetPlayer(player.GetIdentity().GetId()).GetJobGrade());

        g_Game.RPCSingleParam(null, DZL_RPC.EVENT_SEND_CONTACT, new Param1<ref DZLOnlinePlayer>(onlinePlayer), true, targetPlayer.GetIdentity());
    }
}
