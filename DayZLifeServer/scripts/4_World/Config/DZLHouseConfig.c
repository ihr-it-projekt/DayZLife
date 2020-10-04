class DZLHouseConfig: DZLHouseServerConfig {

    void DZLHouseConfig()
	{
        if(!Load()) {
            houseConfigs = new array<ref DZLHouseDefinition>;

            houseConfigs.Insert(new DZLHouseDefinition("1 0 0", "1 0 0", "Land_House_1W03", 100));

            Save();
        }
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "house.json")) {
			JsonFileLoader<DZLHouseConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "house.json", this);
			return true;
        }
		return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
			CheckDZLConfigPath();
			JsonFileLoader<DZLHouseConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "house.json", this);
		}
    }

}