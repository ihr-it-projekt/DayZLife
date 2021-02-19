class DZLMessageListener
{
    void DZLMessageListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLMessageListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_SEND_MESSAGE) {
            PlayerBase player = PlayerBase.Cast(target);
            autoptr Param3<string, string, string> paramMessage;
            if (ctx.Read(paramMessage) && player){
                string receiverId = paramMessage.param1;
                string text = paramMessage.param2;
                string type = paramMessage.param3;

                array<Man> _players = new array<Man>;
                GetGame().GetPlayers(_players);
                DZLMessage message;
                if (_players) {
                    foreach(Man _player: _players) {
                        PlayerBase receiver = PlayerBase.Cast(_player);
                        if ((type != DZLMessage.TYPE_COP && type != DZLMessage.TYPE_MEDIC && paramMessage.param1 == "") || paramMessage.param1 == receiver.GetPlayerId() || (type == DZLMessage.TYPE_COP && receiver.GetDZLPlayer().IsActiveAsCop()) || (type == DZLMessage.TYPE_MEDIC && receiver.GetDZLPlayer().IsActiveAsMedic())) {
                            message = new DZLMessage;
                            message.CreateAndSend(player, _player.GetIdentity(), text, type);
                            if(paramMessage.param1 == receiver.GetPlayerId()) {
                                break;
                            }
                        }
                    }
                }
                if (!message) {
                    DZLSendMessage(sender, "recipient_is_not_online_you_can_not_answer");
                }

           }
        } else if (rpc_type == DAY_Z_LIFE_RECEIVE_ONLINE_PLAYERS) {
            PlayerBase playerGetList = PlayerBase.Cast(target);
            SendOnlinePlayerList(playerGetList);
        }
    }


    private void SendOnlinePlayerList(PlayerBase player) {
        array<Man> _players = new array<Man>;
        GetGame().GetPlayers(_players);
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        DZLPlayerIdentities dzlPlayerIdentities = DZLDatabaseLayer.Get().GetPlayerIds();

        if (_players) {
            foreach(Man _player: _players) {
                string ident = _player.GetIdentity().GetId();
                if (ident == player.GetPlayerId()) continue;
                collection.Insert(new DZLOnlinePlayer(ident, _player.GetIdentity().GetName()));
            }
        }

        GetGame().RPCSingleParam(null, DAY_Z_LIFE_RECEIVE_ONLINE_PLAYERS_RESPONSE, new Param1<ref array<ref DZLOnlinePlayer>>(collection), true, player.GetIdentity());
    }

}
