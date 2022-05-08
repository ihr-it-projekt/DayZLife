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
            DebugMessageDZL("Send Config");
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_HOUSE, new Param1<ref DZLHouseConfig>(config.houseConfig), true, sender);
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_HOUSE_EXTENSION, new Param1<ref DZLHouseExtensions>(config.houseExtensions), true, sender);
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_JOB, new Param1<ref DZLJobConfig>(config.jobConfig), true, sender);
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_LICENCE, new Param1<ref DZLLicenceConfig>(config.licenceConfig), true, sender);
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_COP, new Param1<ref DZLJobSpawnPoints>(config.copSpawnPoints), true, sender);
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_MEDIC, new Param1<ref DZLJobSpawnPoints>(config.medicSpawnPoints), true, sender);
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_ARMY, new Param1<ref DZLJobSpawnPoints>(config.armySpawnPoints), true, sender);
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_CIV, new Param1<ref DZLJobSpawnPoints>(config.civilSpawnPoints), true, sender);
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_ADMIN_IDS, new Param1<ref DZLAdmin>(config.adminIds), true, sender);
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_GET_CONFIG_CAR_RESPONSE, new Param1<ref DZLCarConfig>(config.carConfig), true, sender);
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_GET_CONFIG_MEDIC_RESPONSE, new Param1<ref DZLMedicConfig>(config.medicConfig), true, sender);
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_BANKING, new Param1<ref DZLBankingConfig>(config.bankConfig), true, sender);
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_BASE_BUILDING, new Param1<ref DZLBaseBuildingConfig>(config.baseBuildingConfig), true, sender);
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_CRIME, new Param1<ref DZLCrimeConfig>(config.crimeConfig), true, sender);
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_MESSAGE, new Param1<ref DZLMessageConfig>(config.messageConfig), true, sender);
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_TUNING_CONFIG, new Param1<ref DZLTuningConfig>(config.tuningConfig), true, sender);
        } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_TRADER) {
            GetGame().RPCSingleParam(target, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_TRADER, new Param1<ref DZLTraderConfig>(config.traderConfig), true, sender);
        } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_BANKING) {
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_BANKING, new Param1<ref DZLBankingConfig>(config.bankConfig), true, sender);
        } else if (rpc_type == DAY_Z_LIFE_PLAYER_DATA) {
            DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(sender.GetId());;
            dzlPlayer.UpdateName(sender.GetName());
            dzlPlayer.GetFractionMember();
            GetGame().RPCSingleParam(target, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(dzlPlayer), true, sender);
        }
    }
}
