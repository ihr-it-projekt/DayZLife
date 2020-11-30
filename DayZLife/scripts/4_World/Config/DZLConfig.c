class DZLConfig
{
    ref DZLHouseConfig houseConfig;
    ref DZLHouseExtensions houseExtensions;
	ref DZLBankingConfig bankConfig;
	ref DZLJobConfig jobConfig;
	ref DZLLicenceConfig licenceConfig;
	ref DZLTraderConfig traderConfig;

    void DZLConfig() {
        houseConfig = new DZLHouseConfig;
        houseExtensions = new DZLHouseExtensions;
        bankConfig = new DZLBankingConfig;
        jobConfig = new DZLJobConfig;
		licenceConfig = new DZLLicenceConfig;
		traderConfig = new DZLTraderConfig;
    }
	
	ref array<ref DZLHouseDefinition> GetHouseDefinitions() {
		return houseConfig.houseConfigs;
	}

	ref array<ref DZLHouseExtension> GetExtensions() {
		return houseExtensions.extensions;
	}
}
