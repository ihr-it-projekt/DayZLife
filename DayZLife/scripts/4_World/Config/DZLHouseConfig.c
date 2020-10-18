class DZLHouseConfig {
    ref array<ref DZLHouseDefinition> houseConfigs;

    void DZLHouseConfig()
	{
        if(!Load()) {
            houseConfigs = new array<ref DZLHouseDefinition>;

			array<vector> storagePosition = new array<vector>;
			storagePosition.Insert("4.190976 -1.514594 1.860325");
			storagePosition.Insert("-7.838855 -1.885593 1.504985");
			storagePosition.Insert("2.784797 -1.687099 3.465543");
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