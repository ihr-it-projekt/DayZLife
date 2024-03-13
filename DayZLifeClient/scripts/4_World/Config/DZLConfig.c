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
    private ref DZLJobSpawnPoints copSpawnPoints;
    private ref DZLJobSpawnPoints transportSpawnPoints;
    private ref DZLJobSpawnPoints medicSpawnPoints;
    private ref DZLJobSpawnPoints armySpawnPoints;
    private ref DZLJobSpawnPoints civilSpawnPoints;
    // end deprecated

    ref array<ref DZLJobSpawnPointCollection> jobSpawnPoints = new array<ref DZLJobSpawnPointCollection>;

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
            jobConfig = new DZLJobConfig;
            houseExtensions = new DZLHouseExtensions;
            bankConfig = new DZLBankingConfig;
            licenceConfig = new DZLLicenceConfig;
            traderConfig = new DZLTraderConfig;

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

    DZLJobSpawnPoints GetJobSpawnPointsByJobId(string jobId) {
        foreach(DZLJobSpawnPointCollection collection: jobSpawnPoints) {
            if(collection.jobId == jobId) {
                return collection.spawnPoints;
            }
        }
        return null;
    }
}
