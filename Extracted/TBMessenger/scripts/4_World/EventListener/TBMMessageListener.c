class TBMMessageListener
{
    void TBMMessageListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsTBM);
    }

    void ~TBMMessageListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsTBM);
    }

    void HandleEventsTBM(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_SEND_MESSAGE) {
            PlayerBase player = PlayerBase.Cast(target);
            autoptr Param4<string, string, string, bool> paramMessage;
            if (ctx.Read(paramMessage) && player){
                string receiverId = paramMessage.param1;
                string text = paramMessage.param2;
                string type = paramMessage.param3;
                bool senderVisible = paramMessage.param4;

                TBMMessage message = TBMMessageListener.SendMessage(player, receiverId, text, type, "0 0 0", senderVisible);

                if (!message) {
                    TBMSendMessage(sender, "#recipient_is_not_online_you_can_not_answer");
                }
           }
        } else if (rpc_type == DAY_Z_LIFE_RECEIVE_ONLINE_PLAYERS) {
            PlayerBase playerGetList = PlayerBase.Cast(target);
            SendOnlinePlayerList(playerGetList);
        }
    }

    static TBMMessage SendMessage(PlayerBase player, string receiverId, string text, string type, vector position = "0 0 0", bool senderVisible = true) {
        array<Man> _players = new array<Man>;
        GetGame().GetPlayers(_players);
        TBMMessage message;
        if (_players) {
            foreach(Man _player: _players) {
                PlayerBase receiver = PlayerBase.Cast(_player);
                if (receiverId == receiver.GetPlayerId() || receiverId == "") {
                    message = new TBMMessage;
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
        array<ref TBMOnlinePlayer> collection = new array<ref TBMOnlinePlayer>;

        if (_players) {
            foreach(Man _player: _players) {
                string ident = _player.GetIdentity().GetId();
                if (ident == player.GetPlayerId()) continue;
                collection.Insert(new TBMOnlinePlayer(ident, _player.GetIdentity().GetName()));
            }
        }

        GetGame().RPCSingleParam(null, DAY_Z_LIFE_RECEIVE_ONLINE_PLAYERS_RESPONSE, new Param1<ref array<ref TBMOnlinePlayer>>(collection), true, player.GetIdentity());
    }

}
