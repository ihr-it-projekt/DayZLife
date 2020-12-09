class DZLConfig
{
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
        houseConfig = new DZLHouseConfig;
        houseExtensions = new DZLHouseExtensions;
        bankConfig = new DZLBankingConfig;
        jobConfig = new DZLJobConfig;
		licenceConfig = new DZLLicenceConfig;
		traderConfig = new DZLTraderConfig;
		copSpawnPoints = new DZLJobSpawnPoints(DAY_Z_LIFE_JOB_COP);
        medicSpawnPoints = new DZLJobSpawnPoints(DAY_Z_LIFE_JOB_MEDIC);
        civilSpawnPoints = new DZLJobSpawnPoints(DAY_Z_LIFE_JOB_CIVIL);
        adminIds = new DZLAdmin();

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
	
	bool IsAdmin(PlayerIdentity player) {
		string playerId = player.GetId();
		foreach(string id: adminIds.adminIds) {
			if(playerId == id) {
				return true;
			}
		}
		return false;
	}

	
	ref array<ref DZLHouseDefinition> GetHouseDefinitions() {
		return houseConfig.houseConfigs;
	}

	ref array<ref DZLHouseExtension> GetExtensions() {
		return houseExtensions.extensions;
	}
}
