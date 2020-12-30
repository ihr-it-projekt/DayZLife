class DZLConfigListener
{
    ref DZLConfig config;

    void DZLConfigListener() {
        config = DZLConfig.Get();
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLConfigListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG) {
            autoptr Param1<PlayerBase> paramGetConfig;
            if (ctx.Read(paramGetConfig)){
                DebugMessageDZL("Send Config");
                GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_HOUSE, new Param1<ref DZLHouseConfig>(config.houseConfig), true, sender);
                GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_HOUSE_EXTENSION, new Param1<ref DZLHouseExtensions>(config.houseExtensions), true, sender);
                GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_JOB, new Param1<ref DZLJobConfig>(config.jobConfig), true, sender);
                GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_LICENCE, new Param1<ref DZLLicenceConfig>(config.licenceConfig), true, sender);
                GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_COP, new Param1<ref DZLJobSpawnPoints>(config.copSpawnPoints), true, sender);
                GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_MEDIC, new Param1<ref DZLJobSpawnPoints>(config.medicSpawnPoints), true, sender);
                GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_CIV, new Param1<ref DZLJobSpawnPoints>(config.civilSpawnPoints), true, sender);
                GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_ADMIN_IDS, new Param1<ref DZLAdmin>(config.adminIds), true, sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_TRADER) {
            autoptr Param1<PlayerBase> paramGetConfigTrader;
            if (ctx.Read(paramGetConfigTrader)){
                GetGame().RPCSingleParam(paramGetConfigTrader.param1, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_TRADER, new Param1<ref DZLTraderConfig>(config.traderConfig), true, sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_BANKING) {
            autoptr Param1<PlayerBase> paramGetConfigBanking;
            if (ctx.Read(paramGetConfigBanking)){
                GetGame().RPCSingleParam(paramGetConfigBanking.param1, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_BANKING, new Param1<ref DZLBankingConfig>(config.bankConfig), true, sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_PLAYER_DATA) {
            autoptr Param1<PlayerBase> paramGetPlayerData;
            if (ctx.Read(paramGetPlayerData)){
                if (paramGetPlayerData.param1){
                    DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(sender.GetId());
                    dzlPlayer.UpdateName(sender.GetName());

                    GetGame().RPCSingleParam(paramGetPlayerData.param1, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(dzlPlayer), true, sender);
                }

            }
        }
    }
}
