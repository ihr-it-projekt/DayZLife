class TBMPlayerEventListener
{
    private PlayerBase player;

    void TBMPlayerEventListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsTBM);
    }

    void ~TBMPlayerEventListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsTBM);
    }

    void HandleEventsTBM(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        player = TBMPlayerBaseHelper.GetPlayer();
        if (player) {
            if (rpc_type == DAY_Z_LIFE_RECEIVE_MESSAGE) {
                Param1 <string> tbmMessage;
                if (ctx.Read(tbmMessage) && tbmMessage.param1){
                    player.DisplayMessage(tbmMessage.param1);
                }
            } else if(rpc_type == DAY_Z_LIFE_SEND_MESSAGE_SERVER) {
                Param1<ref TBMMessage> messagesParam;
                if (ctx.Read(messagesParam) && messagesParam.param1){
                     TBMMessage receivedMessage = messagesParam.param1;
                     SEffectManager.CreateSound("TBM_Message_SoundSet", player.GetPosition()).SoundPlay();
                     player.DisplayMessage("#you_got_a_message: " + receivedMessage.GetShortText());
                     TBMMessageDB.Get().AddMessage(receivedMessage);
                     player.RefreshMessageSystem();
                }
            } else if(rpc_type == DAY_Z_LIFE_EVENT_SEND_CONTACT) {
                Param1<ref TBMOnlinePlayer> contactParam;
                if (ctx.Read(contactParam) && contactParam.param1){
                     TBMOnlinePlayer newContact = contactParam.param1;

					if (player) {
						TBMMessageDB.Get().AddContact(newContact);
					}
                }
            }
        }
    }
}
