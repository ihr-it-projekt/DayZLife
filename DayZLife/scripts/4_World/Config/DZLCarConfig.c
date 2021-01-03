class DZLCarConfig
{
    bool carCollisionDamage = false;
    string version = "1";

    void DZLCarConfig() {
        if (!Load()) {
            carCollisionDamage = false;
            Save();
        }
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
