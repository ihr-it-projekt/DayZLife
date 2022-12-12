class TBLOPlayerClientDB
{
    private static ref TBLOPlayerClientDB db;
    private ref TBLOConfig config;
	
    static TBLOPlayerClientDB Get() {
        if (!db) {
            db = new TBLOPlayerClientDB;
        }
        return db;
    }

    void TBLOPlayerClientDB() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsTBLO);
        config = TBLOConfig.Get();
        GetGame().RPCSingleParam(TBLOPlayerBaseHelper.GetPlayer(), TB_LOAD_OUT_GET_CONFIG, null, true);
    }

    void ~TBLOPlayerClientDB() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsTBLO);
    }

    TBLOConfig GetConfig(){
        if (!config) {
            config = TBLOConfig.Get();
        }
		
		if (!config.loadOuts) {
			GetGame().RPCSingleParam(TBLOPlayerBaseHelper.GetPlayer(), TB_LOAD_OUT_GET_CONFIG, null, true);
		}

        return config;
    }


   void HandleEventsTBLO(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        PlayerBase player = TBLOPlayerBaseHelper.GetPlayer();
        if (player) {
            if (rpc_type == TB_LOAD_OUT_CONFIG_RESPONSE) {
                Param1 <ref TBLOLoadOuts> configParamLoadOut;
                if (ctx.Read(configParamLoadOut) && configParamLoadOut.param1) {
                    config.loadOuts = configParamLoadOut.param1;
                }
            }
        }
   }
}