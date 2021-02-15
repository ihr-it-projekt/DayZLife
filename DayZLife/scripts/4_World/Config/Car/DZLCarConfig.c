class DZLCarConfig
{
    bool carCollisionDamage = false;
	bool canStoreCarsWithGoods = false;
	bool canGetCarsFromEveryGarage = true;
	int carRaidTimeInSeconds = 60;
	int chanceToRaid = 2;
	int carInsurancePrice = 2000;
    ref array<ref DZLStoragePosition> garages;
	ref array<string> carTypesToStore;
	ref array<string> carRaidTools;

    string version = "5";

    void DZLCarConfig() {
		array<string> attachments;
        if (!Load()) {
            carCollisionDamage = false;
            garages = new array<ref DZLStoragePosition>;
            carRaidTools = new array<string>;
            carRaidTools.Insert("Lockpick");
            garages.Insert(new DZLStoragePosition("6360.0 9.52 2653.0", "124.0 0.0 0.0", "DZLBaseActionObject", "6365.0 9.1 2648.0", "180 0 0"));

			carTypesToStore = new array<string>;
			carTypesToStore.Insert("OffroadHatchback");
            carTypesToStore.Insert("OffroadHatchback_Blue");
            carTypesToStore.Insert("OffroadHatchback_White");
            carTypesToStore.Insert("Hatchback_02");
            carTypesToStore.Insert("Hatchback_02_Blue");
            carTypesToStore.Insert("Hatchback_02_Black");
            carTypesToStore.Insert("Sedan_02");
            carTypesToStore.Insert("Sedan_02_Red");
            carTypesToStore.Insert("Sedan_02_Grey");
            carTypesToStore.Insert("CivilianSedan");
            carTypesToStore.Insert("CivilianSedan_Wine");
            carTypesToStore.Insert("CivilianSedan_Black");
            carTypesToStore.Insert("Truck_01_Covered");
            carTypesToStore.Insert("Truck_01_Covered_Blue");
            carTypesToStore.Insert("Truck_01_Covered_Orange");

	        canStoreCarsWithGoods = false;
	        carRaidTimeInSeconds = 60;

            version = "3";
            Save();
        }

        if (version == "1") {
            carRaidTools = new array<string>;
            carRaidTools.Insert("Lockpick");
            garages = new array<ref DZLStoragePosition>;
            garages.Insert(new DZLStoragePosition("6360.0 9.52 2653.0", "124.0 0.0 0.0", "SurvivorM_Mirek", "6365.0 9.1 2648.0", "180 0 0"));

			carTypesToStore = new array<string>;
			carTypesToStore.Insert("OffroadHatchback");
            carTypesToStore.Insert("OffroadHatchback_Blue");
            carTypesToStore.Insert("OffroadHatchback_White");
            carTypesToStore.Insert("Hatchback_02");
            carTypesToStore.Insert("Hatchback_02_Blue");
            carTypesToStore.Insert("Hatchback_02_Black");
            carTypesToStore.Insert("Sedan_02");
            carTypesToStore.Insert("Sedan_02_Red");
            carTypesToStore.Insert("Sedan_02_Grey");
            carTypesToStore.Insert("CivilianSedan");
            carTypesToStore.Insert("CivilianSedan_Wine");
            carTypesToStore.Insert("CivilianSedan_Black");
            carTypesToStore.Insert("Truck_01_Covered");
            carTypesToStore.Insert("Truck_01_Covered_Blue");
            carTypesToStore.Insert("Truck_01_Covered_Orange");

            canStoreCarsWithGoods = false;
            carRaidTimeInSeconds = 60;
            version = "2";
            Save();
        }

        if (version == "2") {
            canGetCarsFromEveryGarage = true;
            version = "3";
            Save();
        }

        if (version == "3") {
            carInsurancePrice = 2000;
            version = "4";

            Save();
        }

        if (version == "4") {
            version = "5";
            foreach(DZLStoragePosition garage: garages) {
                garage.type = "DZLBaseActionObject";
            }
            Save();
        }
    }

    DZLStoragePosition GetStorageByPosition(vector playerPosition, int distance = 2) {
        if (!playerPosition) {
            return null;
        }

		foreach(DZLStoragePosition position: garages) {
			float distanceToPos = vector.Distance(position.position, playerPosition);
			if (distanceToPos <= distance){
                return position;
            }
		}

		return null;
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "CarConfig.json")) {
            JsonFileLoader<DZLCarConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "CarConfig.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLCarConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "CarConfig.json", this);
        }
    }
}
