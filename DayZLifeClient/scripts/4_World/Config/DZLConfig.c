class DZLConfig {
    private static ref DZLConfig config;

    static DZLConfig Get() {
        if(!config) {
            config = new DZLConfig;
        }

        return config;
    }

    ref DZLHouseConfig houseConfig;
    ref DZLHouseExtensions houseExtensions;
    ref DZLBankingConfig bankConfig;
    ref DZLJobConfig jobConfig;
    ref DZLLicenceConfig licenceConfig;
    ref DZLTraderConfig traderConfig;

    // deprecated remove 05.03.25
    ref DZLJobSpawnPoints copSpawnPoints;
    ref DZLJobSpawnPoints transportSpawnPoints;
    ref DZLJobSpawnPoints medicSpawnPoints;
    ref DZLJobSpawnPoints armySpawnPoints;
    ref DZLJobSpawnPoints civilSpawnPoints;
    // end deprecated

    ref DZLAdmin adminIds;
    ref DZLCarConfig carConfig;
    ref DZLCarConfig transportConfig;
    ref DZLMedicConfig medicConfig;
    ref DZLBaseBuildingConfig baseBuildingConfig;
    ref DZLCrimeConfig crimeConfig;
    ref DZLMessageConfig messageConfig;
    ref DZLTuningConfig tuningConfig;

    void DZLConfig() {
        if(GetGame().IsServer()) {
            houseExtensions = new DZLHouseExtensions;
            bankConfig = new DZLBankingConfig;
            jobConfig = new DZLJobConfig;
            licenceConfig = new DZLLicenceConfig;
            traderConfig = new DZLTraderConfig;
            copSpawnPoints = new DZLJobSpawnPoints(DAY_Z_LIFE_JOB_COP);
            transportSpawnPoints = new DZLJobSpawnPoints(DAY_Z_LIFE_JOB_TRANSPORT);
            medicSpawnPoints = new DZLJobSpawnPoints(DAY_Z_LIFE_JOB_MEDIC);
            civilSpawnPoints = new DZLJobSpawnPoints(DAY_Z_LIFE_JOB_CIVIL);
            armySpawnPoints = new DZLJobSpawnPoints(DAY_Z_LIFE_JOB_ARMY);
            houseConfig = new DZLHouseConfig(jobConfig.paycheck.jobNames);
            adminIds = new DZLAdmin(jobConfig.paycheck.jobNames);
            carConfig = new DZLCarConfig;
            medicConfig = new DZLMedicConfig;
            baseBuildingConfig = new DZLBaseBuildingConfig;
            crimeConfig = new DZLCrimeConfig;
            messageConfig = new DZLMessageConfig;
            tuningConfig = new DZLTuningConfig;
        }

    }

    DZLJobSpawnPoints GetJobSpanwPointById(string searchJobId) {
        if(searchJobId == DAY_Z_LIFE_JOB_COP) {
            return copSpawnPoints;
        } else if(searchJobId == DAY_Z_LIFE_JOB_MEDIC) {
            return medicSpawnPoints;
        }

        else if(searchJobId == DAY_Z_LIFE_JOB_TRANSPORT) {
            return transportSpawnPoints;
        } else if(searchJobId == DAY_Z_LIFE_JOB_ARMY) {
            return armySpawnPoints;
        }

        return civilSpawnPoints;
    }

    ref array<ref DZLHouseDefinition> GetHouseDefinitions() {
        if(houseConfig && houseConfig.houseConfigs) {
            return houseConfig.houseConfigs;
        }
        return null;
    }

    ref array<ref DZLHouseExtension> GetExtensions() {
        if(houseExtensions && houseExtensions.extensions) {
            return houseExtensions.extensions;
        }
        return null;
    }

    DZLHouseExtension GetHouseExtensionById(string id) {
        array<ref DZLHouseExtension> extensions = GetExtensions();
        if(null == extensions) return null;

        foreach(DZLHouseExtension _extension: extensions) {
            if(_extension.GetId() == id) {
                return _extension;
            }
        }

        return null;
    }
}
