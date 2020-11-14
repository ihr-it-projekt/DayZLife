class DZLConfig
{
    ref DZLHouseConfig houseConfig;
    ref DZLStorageTypes storageTypes;
	ref DZLBankingConfig bankConfig;
	ref DZLJobConfig jobConfig;
	ref DZLLicenceConfig licenceConfig;
	ref DZLTraderConfig traderConfig;

    void DZLConfig() {
        houseConfig = new DZLHouseConfig;
        storageTypes = new DZLStorageTypes;
        bankConfig = new DZLBankingConfig;
        jobConfig = new DZLJobConfig;
		licenceConfig = new DZLLicenceConfig;
		traderConfig = new DZLTraderConfig;
    }
	
	ref array<ref DZLHouseDefinition> GetHouseDefinitions() {
		return houseConfig.houseConfigs;
	}

	ref array<ref DZLStorageType> GetStorageTypes() {
		return storageTypes.storageTypes;
	}
	
	
}