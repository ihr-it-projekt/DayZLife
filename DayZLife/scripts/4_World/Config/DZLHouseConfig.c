class DZLHouseConfig {
    ref array<ref DZLHouseDefinition> houseConfigs;

    void DZLHouseConfig()
	{
        if(!Load()) {
            houseConfigs = new array<ref DZLHouseDefinition>;

			array<vector> storagePosition = new array<vector>;
			storagePosition.Insert("3 4.236272 -4");
			storagePosition.Insert("-1.2002 2.436863 3.5");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_1W03", 100, 50, storagePosition, 0.5));
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