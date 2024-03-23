class DZLMessageListener: DZLBaseEventListener {

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.SEND_MESSAGE) {
            PlayerBase player = PlayerBase.Cast(target);
            autoptr Param4<string, string, string, bool> paramMessage;
            if(ctx.Read(paramMessage) && player) {
                string receiverId = paramMessage.param1;
                string text = paramMessage.param2;
                string type = paramMessage.param3;
                bool senderVisible = paramMessage.param4;

                DZLMessage message = DZLMessageListener.SendMessage(player, receiverId, text, type, "0 0 0", senderVisible);

                if(!message) {
                    DZLSendMessage(sender, "#recipient_is_not_online_you_can_not_answer");
                }
            }
        } else if(rpc_type == DZL_RPC.RECEIVE_ONLINE_PLAYERS) {
            PlayerBase playerGetList = PlayerBase.Cast(target);
            SendOnlinePlayerList(playerGetList);
        }
    }

    static DZLMessage SendMessage(PlayerBase player, string receiverId, string text, string type, vector position = "0 0 0", bool senderVisible = true) {
        array<Man> _players = new array<Man>;
        GetGame().GetPlayers(_players);
        DZLMessage message;
        if(_players) {
            foreach(Man _player: _players) {
                PlayerBase receiver = PlayerBase.Cast(_player);
                if((type != DZLMessage.TYPE_COP && type != DZLMessage.TYPE_MEDIC && receiverId == "") || receiverId == receiver.GetPlayerId() || (type == DZLMessage.TYPE_COP && receiver.GetDZLPlayer().IsActiveJob(DAY_Z_LIFE_JOB_COP)) || (type == DZLMessage.TYPE_MEDIC && receiver.GetDZLPlayer().IsActiveJob(DAY_Z_LIFE_JOB_MEDIC))) {
                    message = new DZLMessage;
                    message.CreateAndSend(player, _player.GetIdentity(), text, type, position, senderVisible);
                    if(receiverId == receiver.GetPlayerId()) {
                        break;
                    }
                }
            }
        }
        return message;
    }


    private void SendOnlinePlayerList(PlayerBase player) {
        array<Man> _players = new array<Man>;
        GetGame().GetPlayers(_players);
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        DZLPlayerIdentities dzlPlayerIdentities = DZLDatabaseLayer.Get().GetPlayerIds();

        if(_players) {
            foreach(Man _player: _players) {
                string ident = _player.GetIdentity().GetId();
                if(ident == player.GetPlayerId()) continue;
                collection.Insert(new DZLOnlinePlayer(ident, _player.GetIdentity().GetName(), DZLDatabaseLayer.Get().GetPlayer(ident).GetJobGrade()));
            }
        }

        GetGame().RPCSingleParam(null, DZL_RPC.RECEIVE_ONLINE_PLAYERS_RESPONSE, new Param1<ref array<ref DZLOnlinePlayer>>(collection), true, player.GetIdentity());
    }

}
