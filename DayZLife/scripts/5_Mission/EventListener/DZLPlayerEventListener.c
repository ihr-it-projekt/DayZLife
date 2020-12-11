class DZLPlayerEventListener
{
    private PlayerBase player;
	private ScriptCallQueue queue;

    void DZLPlayerEventListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLPlayerEventListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        player = PlayerBaseHelper.GetPlayer();
        if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE) {
            Param1 <ref DZLConfig> configParam;
            if (ctx.Read(configParam) && configParam.param1){
                DebugMessageDZL("Initialize DZLConfig");
                player.config = configParam.param1;
                player.IsRealPlayer = true;
            }
        } else if (rpc_type == DAY_Z_LIFE_GET_PLAYER_BUILDING_RESPONSE) {
            Param1 <ref DZLPlayerHouse> houseParam;
            if (ctx.Read(houseParam) && houseParam.param1){
                DebugMessageDZL("Initialize DZLPlayerHouse");
                player.house = houseParam.param1;
            }
        } else if (rpc_type == DAY_Z_LIFE_PLAYER_DATA_RESPONSE) {
            Param1 <ref DZLPlayer> dzlPlayerParam;
            if (ctx.Read(dzlPlayerParam) && dzlPlayerParam.param1){
                DebugMessageDZL("Initialize DZLPlayer");
                player.dzlPlayer = dzlPlayerParam.param1;
                player.UpdatePlayerAtDependencies();
            }
        } else if (rpc_type == DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE) {
            Param1 <ref DZLBank> dzlBankParam;
            if (ctx.Read(dzlBankParam) && dzlBankParam.param1){
                DebugMessageDZL("Initialize Bank");
                player.dzlBank = dzlBankParam.param1;
            }
        } else if (rpc_type == DAY_Z_LIFE_RECEIVE_MESSAGE) {
            Param1 <string> dzlMessage;
            if (ctx.Read(dzlMessage) && dzlMessage.param1){
                DebugMessageDZL("Receive Message");
                player.DisplayMessage(dzlMessage.param1);
            }
        } else if (rpc_type == DAY_Z_LIFE_NEW_SPAWN_CLIENT) {
            queue = GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM);
            queue.CallLater(CreateSpawnMenu, 1750, true);
        } else if(rpc_type == DAY_Z_LIFE_HOUSE_RAID_ALARM) {
            Param3<ref DZLHouseExtension, string, PlayerBase> dzlAlarm;
            if (ctx.Read(dzlAlarm) && dzlAlarm.param1 && dzlAlarm.param2 && dzlAlarm.param3){
                 player.DisplayMessage(dzlAlarm.param1.GetMessage(dzlAlarm.param3, dzlAlarm.param2));
            }
        }
    }

    void CreateSpawnMenu() {
        player = PlayerBaseHelper.GetPlayer();
        if (!player || !player.config) {
            return;
        }

        queue = GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM);
        queue.Remove(CreateSpawnMenu);

        GetGame().GetUIManager().CloseAll();
        GetGame().GetUIManager().ShowScriptedMenu(player.GetSpawnPositionMenu(), null);
    }

}
