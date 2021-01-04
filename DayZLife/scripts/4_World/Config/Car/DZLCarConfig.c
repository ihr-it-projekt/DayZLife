class DZLCarConfig
{
    bool carCollisionDamage = false;
    ref array<ref DZLStoragePosition> garages;
	ref array<string> carTypesToStore;

    string version = "2";

    void DZLCarConfig() {
		array<string> attachments;
        if (!Load()) {
            carCollisionDamage = false;
            garages = new array<ref DZLStoragePosition>;
            attachments = new array<string>;
            attachments.Insert("SlacksPants_White");
            attachments.Insert("DressShoes_White");
            attachments.Insert("ManSuit_White");
            attachments.Insert("AviatorGlasses");
            garages.Insert(new DZLStoragePosition("6342.443359 8.952032 2733.456299", "121.344437 0.0 0.0", "SurvivorM_Mirek", attachments, "6348.307129 8.771828 2722.534668", "0 0 0"));

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

            version = "2";
            Save();
        }

        if (version == "1") {
            attachments = new array<string>;
            attachments.Insert("SlacksPants_White");
            attachments.Insert("DressShoes_White");
            attachments.Insert("ManSuit_White");
            attachments.Insert("AviatorGlasses");
            garages = new array<ref DZLStoragePosition>;
            garages.Insert(new DZLStoragePosition("6342.443359 8.952032 2733.456299", "121.344437 0.0 0.0", "SurvivorM_Mirek", attachments, "6348.307129 8.771828 2722.534668", "0 0 0"));

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

            version = "2";
            Save();
        }
    }

    DZLStoragePosition GetStorageByPosition(PlayerBase player, int distance = 2) {
		vector playerPosition = player.GetPosition();
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
