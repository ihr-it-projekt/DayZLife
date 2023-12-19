class DZLBaseBuildingConfig {
    string version = "1";
    bool canCraftFenceKit = false;
    bool canCraftShelterKit = false;
    bool canCraftTerritoryFlagKit = false;
    bool canCraftWatchtowerKit = false;

    void DZLBaseBuildingConfig() {
        if (!Load()) {
            Save();
        }
    }

    private bool Load() {
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "BaseBuilding.json")) {
            JsonFileLoader<DZLBaseBuildingConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "BaseBuilding.json", this);
            return true;
        }
        return false;
    }

    private void Save() {
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLBaseBuildingConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "BaseBuilding.json", this);
        }
    }
}