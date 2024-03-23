modded class DZLBaseBuildingConfig {

    void DZLBaseBuildingConfig() {
        if(!Load()) Save();
    }

    private bool Load() {
        if(FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "BaseBuilding.json")) {
            JsonFileLoader<DZLBaseBuildingConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "BaseBuilding.json", this);
            return true;
        }
        return false;
    }

    private void Save() {
        JsonFileLoader<DZLBaseBuildingConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "BaseBuilding.json", this);
    }
}