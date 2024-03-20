class DZLPlayerEventListener: DZLBaseEventListener {
    private PlayerBase player;
    private ScriptCallQueue queue;

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.NEW_SPAWN_CLIENT) {
            queue = GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM);
            queue.CallLater(CreateSpawnMenu, 1750, true);
            return;
        }

        player = DZLPlayerBaseHelper.GetPlayer();
        if(!player) return;

        if(rpc_type == DZL_RPC.RECEIVE_MESSAGE) {
            Param1 <string> dzlMessage;
            if(ctx.Read(dzlMessage) && dzlMessage.param1) {
                player.DisplayMessage(dzlMessage.param1);
            }
        } else if(rpc_type == DZL_RPC.RECEIVE_MEDIC_MESSAGE) {
            Param1 <string> dzlMessageMedic;
            if(ctx.Read(dzlMessageMedic) && dzlMessageMedic.param1) {
                player.DisplayMessage(dzlMessageMedic.param1);
            }
        } else if(rpc_type == DZL_RPC.SEND_MESSAGE_SERVER) {
            Param1<ref DZLMessage> messagesParam;
            if(ctx.Read(messagesParam) && messagesParam.param1) {
                DZLMessage receivedMessage = messagesParam.param1;
                SEffectManager.CreateSound("DZL_Message_SoundSet", player.GetPosition()).SoundPlay();
                player.DisplayMessage("#you_got_a_message: " + receivedMessage.GetShortText());
                DZLMessageDB.Get().AddMessage(receivedMessage);
                player.RefreshMessageSystem();
            }
        } else if(rpc_type == DZL_RPC.EVENT_SEND_CONTACT) {
            Param1<ref DZLOnlinePlayer> contactParam;
            if(ctx.Read(contactParam) && contactParam.param1) {
                DZLOnlinePlayer newContact = contactParam.param1;
                DZLPlayer dzlPlayer = player.GetDZLPlayer();

                if(dzlPlayer) {
                    dzlPlayer.AddToContact(newContact);
                }
            }
        }
    }

    void CreateSpawnMenu() {
        player = DZLPlayerBaseHelper.GetPlayer();
        if(!player || !DZLConfig.Get() || !player.GetDZLPlayer()) return;

        queue = GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM);
        queue.Remove(CreateSpawnMenu);

        GetGame().GetUIManager().CloseAll();
        GetGame().GetUIManager().ShowScriptedMenu(player.GetSpawnPositionMenu(), null);
    }

    void PlayerRespawn() {
        GetGame().GetMenuDefaultCharacterData(false).SetRandomCharacterForced(true);
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(GetGame().RespawnPlayer);

        MissionGameplay missionGP = MissionGameplay.Cast(GetGame().GetMission());
        missionGP.DestroyAllMenus();
        missionGP.SetPlayerRespawning(true);

        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(GetGame().GetMission().Continue);
    }

}
