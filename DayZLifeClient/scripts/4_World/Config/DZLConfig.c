class DZLConfig extends DZLBaseEventListener {
    private static ref DZLConfig config;

    static DZLConfig Get() {
        if(!config) {
            config = new DZLConfig;
        }

        return config;
    }

    void DZLConfig() {
        GetGame().RPCSingleParam(DZLPlayerBaseHelper.GetPlayer(), DZL_RPC.EVENT_GET_CONFIG, null, true);
    }

    ref DZLHouseConfig houseConfig;
    ref DZLBankingConfig bankConfig;
    ref DZLJobConfig jobConfig;
    ref DZLLicenceConfig licenceConfig;
    ref DZLTraderConfig traderConfig;
    ref array<ref DZLJobSpawnPointCollection> jobSpawnPoints = new array<ref DZLJobSpawnPointCollection>;
    ref DZLAdmin adminIds;
    ref DZLCarConfig carConfig;
    ref DZLBaseBuildingConfig baseBuildingConfig;
    ref DZLCrimeConfig crimeConfig;
    ref DZLMessageConfig messageConfig;
    ref DZLTuningConfig tuningConfig;

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.EVENT_GET_CONFIG_RESPONSE_BANKING) {
            Param1 <ref DZLBankingConfig> configParamBanking;
            if(ctx.Read(configParamBanking) && configParamBanking.param1) {
                bankConfig = configParamBanking.param1;
            }
        } else if(rpc_type == DZL_RPC.EVENT_GET_CONFIG_RESPONSE_HOUSE_CONFIG) {
            Param1 <ref DZLHouseConfig> configParamHouse;
            if(ctx.Read(configParamHouse) && configParamHouse.param1) {
                houseConfig = configParamHouse.param1;
            }
        } else if(rpc_type == DZL_RPC.EVENT_GET_CONFIG_RESPONSE_BASE_BUILDING) {
            Param1 <ref DZLBaseBuildingConfig> configParamBaseBuilding;
            if(ctx.Read(configParamBaseBuilding) && configParamBaseBuilding.param1) {
                baseBuildingConfig = configParamBaseBuilding.param1;
            }
        } else if(rpc_type == DZL_RPC.EVENT_GET_CONFIG_RESPONSE_JOB) {
            Param1 <ref DZLJobConfig> configParamJob;
            if(ctx.Read(configParamJob) && configParamJob.param1) {
                jobConfig = configParamJob.param1;
            }
        } else if(rpc_type == DZL_RPC.EVENT_GET_CONFIG_RESPONSE_LICENCE) {
            Param1 <ref DZLLicenceConfig> configParamLicence;
            if(ctx.Read(configParamLicence) && configParamLicence.param1) {
                licenceConfig = configParamLicence.param1;
            }
        } else if(rpc_type == DZL_RPC.EVENT_GET_CONFIG_RESPONSE_TRADER) {
            Param1 <ref DZLTraderConfig> configParamTrader;
            if(ctx.Read(configParamTrader) && configParamTrader.param1) {
                traderConfig = configParamTrader.param1;
            }
        } else if(rpc_type == DZL_RPC.EVENT_GET_CONFIG_RESPONSE_SPAWN_POINTS) {
            Param1 <ref array<ref DZLJobSpawnPointCollection>> configParamjobSpawnPoints;
            if(ctx.Read(configParamjobSpawnPoints) && configParamjobSpawnPoints.param1) {
                jobSpawnPoints = configParamjobSpawnPoints.param1;
            }
        } else if(rpc_type == DZL_RPC.EVENT_GET_CONFIG_RESPONSE_ADMIN_IDS) {
            Param1 <ref DZLAdmin> configParamAdmin;
            if(ctx.Read(configParamAdmin) && configParamAdmin.param1) {
                adminIds = configParamAdmin.param1;
            }
        } else if(rpc_type == DZL_RPC.EVENT_GET_CONFIG_CAR_RESPONSE) {
            Param1 <ref DZLCarConfig> configParamCar;
            if(ctx.Read(configParamCar) && configParamCar.param1) {
                carConfig = configParamCar.param1;
            }
        } else if(rpc_type == DZL_RPC.EVENT_GET_CONFIG_RESPONSE_CRIME) {
            Param1 <ref DZLCrimeConfig> crimeParam;
            if(ctx.Read(crimeParam) && crimeParam.param1) {
                crimeConfig = crimeParam.param1;
            }
        } else if(rpc_type == DZL_RPC.EVENT_GET_CONFIG_RESPONSE_MESSAGE) {
            Param1 <ref DZLMessageConfig> dzlMessageParam;
            if(ctx.Read(dzlMessageParam) && dzlMessageParam.param1) {
                messageConfig = dzlMessageParam.param1;
            }
        } else if(rpc_type == DZL_RPC.EVENT_GET_CONFIG_RESPONSE_TUNING_CONFIG) {
            Param1 <ref DZLTuningConfig> dzlTuningConfigParam;
            if(ctx.Read(dzlTuningConfigParam) && dzlTuningConfigParam.param1) {
                tuningConfig = dzlTuningConfigParam.param1;
            }
        }
    }

    DZLJobSpawnPoints GetJobSpawnPointsByJobId(string jobId) {
        foreach(DZLJobSpawnPointCollection collection: jobSpawnPoints) {
            if(collection.jobId == jobId) {
                return collection.spawnPoints;
            }
        }
        return null;
    }
}
