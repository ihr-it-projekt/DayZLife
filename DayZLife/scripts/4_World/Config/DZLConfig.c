class DZLConfig
{
    private ref DZLHouseConfig houseConfig;
    private ref DZLStorageTypes storageTypes;
	ref DZLBankingConfig bankConfig;
	ref DZLJobConfig jobConfig;

    void DZLConfig() {
        houseConfig = new DZLHouseConfig;
        storageTypes = new DZLStorageTypes;
        bankConfig = new DZLBankingConfig;
        jobConfig = new DZLJobConfig;
    }
	
	ref array<ref DZLHouseDefinition> GetHouseDefinitions() {
		return houseConfig.houseConfigs;
	}

	ref array<ref DZLStorageType> GetStorageTypes() {
		return storageTypes.storageTypes;
	}
	
	
}