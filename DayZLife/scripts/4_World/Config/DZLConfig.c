class DZLConfig
{
    private ref DZLMoneyConfig moneyConfig;
    private ref DZLHouseConfig houseConfig;
    private ref DZLStorageTypes storageTypes;

    void DZLConfig() {
        moneyConfig = new DZLMoneyConfig;
        houseConfig = new DZLHouseConfig;
        storageTypes = new DZLStorageTypes;
    }
	
	ref array<ref DZLHouseDefinition> GetHouseDeinitions() {
		return houseConfig.houseConfigs;
	}

	ref map <string, int> GetMoneyConfing() {
		return moneyConfig.currencyValues;
	}
	
	ref array<ref DZLStorageType> GetStorageTypes() {
		return storageTypes.storageTypes;
	}
}