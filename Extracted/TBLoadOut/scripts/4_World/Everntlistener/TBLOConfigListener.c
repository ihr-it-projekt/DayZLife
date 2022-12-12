class TBLOConfigListener
{
    ref TBLOConfig config;

    void TBLOConfigListener() {
        config = TBLOConfig.Get();
        GetDayZGame().Event_OnRPC.Insert(HandleEventsTBLO);
    }

    void ~TBLOConfigListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsTBLO);
    }

    void HandleEventsTBLO(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == TB_LOAD_OUT_GET_CONFIG) {
            GetGame().RPCSingleParam(null, TB_LOAD_OUT_CONFIG_RESPONSE, new Param1<ref TBLOLoadOuts>(config.loadOuts), true, sender);
        }
    }
}
