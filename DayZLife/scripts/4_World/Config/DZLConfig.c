class DZLConfig
{
    ref DZLHouseConfig houseConfig;
    ref DZLStorageTypes storageTypes;
	ref DZLBankingConfig bankConfig;
	ref DZLJobConfig jobConfig;
	ref DZLLicenceConfig licenceConfig;

    void DZLConfig() {
        houseConfig = new DZLHouseConfig;
        storageTypes = new DZLStorageTypes;
        bankConfig = new DZLBankingConfig;
        jobConfig = new DZLJobConfig;
		licenceConfig = new DZLLicenceConfig;
		
    }
	
	ref array<ref DZLHouseDefinition> GetHouseDefinitions() {
		return houseConfig.houseConfigs;
	}

	ref array<ref DZLStorageType> GetStorageTypes() {
		return storageTypes.storageTypes;
	}
	
	
}