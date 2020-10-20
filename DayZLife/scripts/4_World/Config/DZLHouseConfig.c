class DZLHouseConfig {
    ref array<ref DZLHouseDefinition> houseConfigs;

    void DZLHouseConfig()
	{
        if(!Load()) {
            houseConfigs = new array<ref DZLHouseDefinition>;

			array<vector> storagePosition = new array<vector>;
            houseConfigs.Insert(new DZLHouseDefinition("Land_Garage_Row_Small", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
            houseConfigs.Insert(new DZLHouseDefinition("Land_Shed_W6", 100, 50, storagePosition, 0.5));

			storagePosition = new array<vector>;
			storagePosition.Insert("2 -3.2 7");
			storagePosition.Insert("-2.299805 -3.190286 3");
			storagePosition.Insert("0 -0.09 0");
            houseConfigs.Insert(new DZLHouseDefinition("Land_Garage_Office", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("-8 -5.83 8");
			storagePosition.Insert("-12 -5.82 -8.600098");
			storagePosition.Insert("-4.5 -2.5 7");
			storagePosition.Insert("-4.599609 1.37 7");
            houseConfigs.Insert(new DZLHouseDefinition("Land_Factory_Small", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("0 -2.82 1");
			storagePosition.Insert("3.200195 -2.82 3.799805");
			storagePosition.Insert("-4.200195 0 5.200195");
			storagePosition.Insert("6 -2.82 9");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_1B01_Pub", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("-0.821289 -1.452631 -0.679687");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_1W10", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("-0.821289 -1.452631 -0.679687");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_1W10_Brown", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("-3 -2.46 4");
			storagePosition.Insert("1.200195 -2.46 -3.5");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_1W03", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("-5.5 -1.97 1");
			storagePosition.Insert("-2.5 -1.97 -3.799805");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_1W09_Yellow", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("-1.991211 -2.67 -4.677246");
			storagePosition.Insert("-0.910156 -2.67 4.00293");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_1W04", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("3.045898 -3.22 3.450195");
			storagePosition.Insert("-0.266602 0 1.804688");
			storagePosition.Insert("-6.149414 -3.22 -0.875977");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_2W01", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("-0.78418 -1.89 3.508301");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_1W08", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("-0.78418 -1.89 3.508301");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_1W08_Brown", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("2.901367 -5.58 2.214844");
			storagePosition.Insert("2.94043 -5.58 0.40332");
			storagePosition.Insert("-2.879883 -5.58 2.422852");
			storagePosition.Insert("-2.866211 -5.58 0.37207");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_2B02", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("2.013672 -4.18 4.148926");
			storagePosition.Insert("-0.388672 -1.03 4.246582");
			storagePosition.Insert("1.772461 -1.03 4.25");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_2B01", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("4.045898 -3.11 0");
			storagePosition.Insert("-1.148437 -3.11 0.037598");
			storagePosition.Insert("-5.041992 -3.11 -7.528809");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_1W07", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("-2.516602 -2.65 -2.958008");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_1W11", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("4.485352 -1.024 -1.217285");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_1W05", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("4.485352 -1.024 -1.217285");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_1W05_Yellow", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("-3.883789 -2.86 2.432129");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_1W01", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("-1.719727 -0.912988 0.538574");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_1W06", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("6.018555 -4.05 0.299805");
			storagePosition.Insert("2.394531 -1.299999 1.401855");
			storagePosition.Insert("6.12207 -1.299999 -1.55957");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_2W02", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("-2.71582 -5.559998 3.258789");
			storagePosition.Insert("-5.491211 -0.769997 -0.188965");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_2W03", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("-4.385742 -5.169998 3.672363");
			storagePosition.Insert("3.120117 -0.800003 3.993652");
			storagePosition.Insert("7.071289 -0.800003 2.034668");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_2W04", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("-4.385742 -5.169998 3.672363");
			storagePosition.Insert("3.120117 -0.800003 3.993652");
			storagePosition.Insert("7.071289 -0.800003 2.034668");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_2W04_Yellow", 100, 50, storagePosition, 0.5));
			
			storagePosition = new array<vector>;
			storagePosition.Insert("0.268555 -5.509995 6.685059");
			storagePosition.Insert("1.824219 -2.240005 -1.942383");
            houseConfigs.Insert(new DZLHouseDefinition("Land_House_2B03", 100, 50, storagePosition, 0.5));
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