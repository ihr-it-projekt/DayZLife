class DZLConfig
{
    private ref DZLHouseConfig houseConfig;
    private ref DZLStorageTypes storageTypes;

    void DZLConfig() {
        houseConfig = new DZLHouseConfig;
        storageTypes = new DZLStorageTypes;
    }
	
	ref array<ref DZLHouseDefinition> GetHouseDefinitions() {
		return houseConfig.houseConfigs;
	}

	ref array<ref DZLStorageType> GetStorageTypes() {
		return storageTypes.storageTypes;
	}
}