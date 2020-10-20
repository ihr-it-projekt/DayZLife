class DZLHouseConfig {
    ref array<ref DZLHouseDefinition> houseConfigs;

    void DZLHouseConfig()
	{
        if(!Load()) {
            houseConfigs = new array<ref DZLHouseDefinition>;

			array<vector> storagePosition = new array<vector>;
			storagePosition.Insert("2 -3.066208 7");
			storagePosition.Insert("-2.2998 -3.190361 3");
			storagePosition.Insert("0 -0.073722 0");
            houseConfigs.Insert(new DZLHouseDefinition("Land_Garage_Office", 100, 50, storagePosition, 0.5));

			storagePosition = new array<vector>;
			storagePosition.Insert("-8 -5.807848 8");
			storagePosition.Insert("-12 -6.045334 -8.600098");
			storagePosition.Insert("-4.5 -2.491247 7");
			storagePosition.Insert("-4.59961 1.383093 7");
            houseConfigs.Insert(new DZLHouseDefinition("Land_Factory_Small", 100, 50, storagePosition, 0.5));

			storagePosition = new array<vector>;
			storagePosition.Insert("0 -2.802106 1");
			storagePosition.Insert("3.2002 -2.802106 3.799805");
			storagePosition.Insert("-1 -2.802106 9");
			storagePosition.Insert("6 -3.391876 9");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_1B01_Pub", 100, 50, storagePosition, 0.5));

			storagePosition = new array<vector>;
			storagePosition.Insert("-1 -3.959872 -0.700195");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_1W10", 100, 50, storagePosition, 0.5));

			storagePosition = new array<vector>;
			storagePosition.Insert("-1 -3.959872 -0.700195");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_1W10_Brown", 100, 50, storagePosition, 0.5));

			storagePosition = new array<vector>;
			storagePosition.Insert("-3 -2.436863 4");
			storagePosition.Insert("4.2002 -2.436863 -7.5");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_1W03", 100, 50, storagePosition, 0.5));

			storagePosition = new array<vector>;
			storagePosition.Insert("-5.5 -1.950626 1");
			storagePosition.Insert("-2.5 -1.707117 -3.799805");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_1W09_Yellow", 100, 50, storagePosition, 0.5));

			storagePosition = new array<vector>;
			storagePosition.Insert("0 -2.66 4");
			storagePosition.Insert("-2.2998 -2.66 -4.70117");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_1W04", 100, 50, storagePosition, 0.5));
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