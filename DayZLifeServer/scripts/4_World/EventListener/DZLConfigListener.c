class DZLConfigListener
{
    ref DZLConfig config;

    void DZLConfigListener() {
        config = new DZLConfig;
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLConfigListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG) {
            autoptr Param1<PlayerBase> paramGetConfig;
            if (ctx.Read(paramGetConfig)){
                DebugMessageServerDZL("Send Config");
                GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE, new Param1<ref DZLConfig>(config), true, sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_PLAYER_DATA) {
            autoptr Param1<PlayerBase> paramGetPlayerData;
            if (ctx.Read(paramGetPlayerData)){
                DebugMessageServerDZL("Send player data");
                GetGame().RPCSingleParam(paramGetPlayerData.param1, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(new DZLPlayer(paramGetPlayerData.param1)), true, sender);
            }
        }
    }
}