class TBMConfigListener
{
    ref TBMConfig config;

    void TBMConfigListener() {
        config = TBMConfig.Get();
        GetDayZGame().Event_OnRPC.Insert(HandleEventsTBM);
    }

    void ~TBMConfigListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsTBM);
    }

    void HandleEventsTBM(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG) {
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_MESSAGE, new Param1<ref TBMMessageConfig>(config.messageConfig), true, sender);
        }
    }
}
