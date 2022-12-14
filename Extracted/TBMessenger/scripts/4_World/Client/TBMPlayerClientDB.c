class TBMPlayerClientDB
{
    private static ref TBMPlayerClientDB db;

    private ref TBMConfig config;

    static TBMPlayerClientDB Get() {
        if (!db) {
            db = new TBMPlayerClientDB;
            GetGame().RPCSingleParam(TBMPlayerBaseHelper.GetPlayer(), DAY_Z_LIFE_EVENT_GET_CONFIG, null, true);
        }
        return db;
    }

    void TBMPlayerClientDB() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsTBM);
    }

    void ~TBMPlayerClientDB() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsTBM);
    }

    TBMConfig GetConfig(){
        if (!config) {
            GetGame().RPCSingleParam(TBMPlayerBaseHelper.GetPlayer(), DAY_Z_LIFE_EVENT_GET_CONFIG, null, true);
            config = TBMConfig.Get();
        }

        return config;
    }

   void HandleEventsTBM(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        PlayerBase player = TBMPlayerBaseHelper.GetPlayer();
        if (player) {

           if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_MESSAGE) {
                Param1 <ref TBMMessageConfig> tbmMessageParam;
                if (ctx.Read(tbmMessageParam) && tbmMessageParam.param1){
                    config.messageConfig = tbmMessageParam.param1;
                }
            }
        }
   }
}