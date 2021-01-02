class DZLConfig
{
    private static ref DZLConfig config;

    static DZLConfig Get() {
        if (!config) {
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
	ref DZLJobSpawnPoints copSpawnPoints;
    ref DZLJobSpawnPoints medicSpawnPoints;
    ref DZLJobSpawnPoints civilSpawnPoints;
    ref array<string> jobIds;
    ref DZLAdmin adminIds;

    void DZLConfig() {
        if (GetGame().IsServer()) {
            houseConfig = new DZLHouseConfig;
            houseExtensions = new DZLHouseExtensions;
            bankConfig = new DZLBankingConfig;
            jobConfig = new DZLJobConfig;
            licenceConfig = new DZLLicenceConfig;
            traderConfig = new DZLTraderConfig;
            copSpawnPoints = new DZLJobSpawnPoints(DAY_Z_LIFE_JOB_COP);
            medicSpawnPoints = new DZLJobSpawnPoints(DAY_Z_LIFE_JOB_MEDIC);
            civilSpawnPoints = new DZLJobSpawnPoints(DAY_Z_LIFE_JOB_CIVIL);
            adminIds = new DZLAdmin;
        }

        jobIds = new array<string>;
        jobIds.Insert(DAY_Z_LIFE_JOB_CIVIL);
        jobIds.Insert(DAY_Z_LIFE_JOB_MEDIC);
        jobIds.Insert(DAY_Z_LIFE_JOB_COP);
    }

    DZLJobSpawnPoints GetJobSpanwPointById(string searchJobId) {
        if (searchJobId == DAY_Z_LIFE_JOB_COP) {
            return copSpawnPoints;
        } else if (searchJobId == DAY_Z_LIFE_JOB_MEDIC) {
            return medicSpawnPoints;
        }

        return civilSpawnPoints;
    }

	ref array<ref DZLHouseDefinition> GetHouseDefinitions() {
		return houseConfig.houseConfigs;
	}

	ref array<ref DZLHouseExtension> GetExtensions() {
		return houseExtensions.extensions;
	}
}
