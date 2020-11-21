class DZLPlayerHouseListener
{
    ref DZLConfig config;

    void DZLPlayerHouseListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLPlayerHouseListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_GET_PLAYER_BUILDING) {
            autoptr Param1<PlayerBase> paramGetConfig;
            if (ctx.Read(paramGetConfig)){
                if (paramGetConfig.param1) {
                    GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_GET_PLAYER_BUILDING_RESPONSE, new Param1<ref DZLPlayerHouse>(new DZLPlayerHouse(sender)), true, sender);
                }
            }
        }
    }
}