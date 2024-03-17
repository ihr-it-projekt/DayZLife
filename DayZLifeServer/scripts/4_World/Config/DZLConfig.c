modded class DZLConfig {

    override static DZLConfig Get() {
        if(!config) {
            config = new DZLConfig;
        }

        return config;
    }

    static void Reload() {
        DZLDatabaseLayer.Reload();
        config = new DZLConfig;
        config.UpdateConfig(null);
        DZLBuilderManager.Get().Reload();
    }

    void DZLConfig() {
        jobConfig = new DZLJobConfig;
        bankConfig = new DZLBankingConfig;
        licenceConfig = new DZLLicenceConfig;
        traderConfig = new DZLTraderConfig;

        jobSpawnPoints.Insert(new DZLJobSpawnPointCollection(DAY_Z_LIFE_JOB_CIVIL));
        foreach(string jobId: jobConfig.paycheck.jobNames) {
            jobSpawnPoints.Insert(new DZLJobSpawnPointCollection(jobId));
        }

        houseConfig = new DZLHouseConfig(jobConfig.paycheck.jobNames);
        adminIds = new DZLAdmin(jobConfig.paycheck.jobNames);
        carConfig = new DZLCarConfig;
        medicConfig = new DZLMedicConfig;
        baseBuildingConfig = new DZLBaseBuildingConfig;
        crimeConfig = new DZLCrimeConfig;
        messageConfig = new DZLMessageConfig;
        tuningConfig = new DZLTuningConfig;
    }

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.EVENT_GET_CONFIG) {
            UpdateConfig(sender);
        } else if(rpc_type == DZL_RPC.EVENT_GET_CONFIG_TRADER) {
            GetGame().RPCSingleParam(null, DZL_RPC.EVENT_GET_CONFIG_RESPONSE_TRADER, new Param1<ref DZLTraderConfig>(traderConfig), true, sender);
        } else if(rpc_type == DZL_RPC.EVENT_GET_CONFIG_BANKING) {
            GetGame().RPCSingleParam(null, DZL_RPC.EVENT_GET_CONFIG_RESPONSE_BANKING, new Param1<ref DZLBankingConfig>(bankConfig), true, sender);
        }
    }

    void UpdateConfig(PlayerIdentity sender) {
        GetGame().RPCSingleParam(null, DZL_RPC.EVENT_GET_CONFIG_RESPONSE_JOB, new Param1<ref DZLJobConfig>(jobConfig), true, sender);
        GetGame().RPCSingleParam(null, DZL_RPC.EVENT_GET_CONFIG_RESPONSE_LICENCE, new Param1<ref DZLLicenceConfig>(licenceConfig), true, sender);
        GetGame().RPCSingleParam(null, DZL_RPC.EVENT_GET_CONFIG_RESPONSE_SPAWN_POINTS, new Param1<ref array<ref DZLJobSpawnPointCollection>>(jobSpawnPoints), true, sender);
        GetGame().RPCSingleParam(null, DZL_RPC.EVENT_GET_CONFIG_RESPONSE_ADMIN_IDS, new Param1<ref DZLAdmin>(adminIds), true, sender);
        GetGame().RPCSingleParam(null, DZL_RPC.EVENT_GET_CONFIG_CAR_RESPONSE, new Param1<ref DZLCarConfig>(carConfig), true, sender);
        GetGame().RPCSingleParam(null, DZL_RPC.EVENT_GET_CONFIG_MEDIC_RESPONSE, new Param1<ref DZLMedicConfig>(medicConfig), true, sender);
        GetGame().RPCSingleParam(null, DZL_RPC.EVENT_GET_CONFIG_RESPONSE_BANKING, new Param1<ref DZLBankingConfig>(bankConfig), true, sender);
        GetGame().RPCSingleParam(null, DZL_RPC.EVENT_GET_CONFIG_RESPONSE_BASE_BUILDING, new Param1<ref DZLBaseBuildingConfig>(baseBuildingConfig), true, sender);
        GetGame().RPCSingleParam(null, DZL_RPC.EVENT_GET_CONFIG_RESPONSE_CRIME, new Param1<ref DZLCrimeConfig>(crimeConfig), true, sender);
        GetGame().RPCSingleParam(null, DZL_RPC.EVENT_GET_CONFIG_RESPONSE_MESSAGE, new Param1<ref DZLMessageConfig>(messageConfig), true, sender);
        GetGame().RPCSingleParam(null, DZL_RPC.EVENT_GET_CONFIG_RESPONSE_TUNING_CONFIG, new Param1<ref DZLTuningConfig>(tuningConfig), true, sender);
        GetGame().RPCSingleParam(null, DZL_RPC.EVENT_GET_CONFIG_RESPONSE_HOUSE_CONFIG, new Param1<ref DZLHouseConfig>(houseConfig), true, sender);

        if(null == sender) {
            GetGame().RPCSingleParam(null, DZL_RPC.EVENT_GET_CONFIG_RESPONSE_TRADER, new Param1<ref DZLTraderConfig>(traderConfig), true, sender);
            GetGame().RPCSingleParam(null, DZL_RPC.EVENT_GET_CONFIG_RESPONSE_BANKING, new Param1<ref DZLBankingConfig>(bankConfig), true, sender);
        }
    }
}