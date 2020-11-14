class DZLTraderListener
{
    ref DZLTraderConfig config;

    void DZLTraderListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
        config = new DZLTraderConfig;
    }

    void ~DZLTraderListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_TRADE_ACTION) {
			GetGame().RPCSingleParam(target, DAY_Z_LIFE_TRADE_ACTION_RESPONSE, new Param1<string>("server hat geantwortet"), true, sender);
        }
    }
}