modded class DZLMessageConfig {

    void DZLMessageConfig() {
        if(!Load()) {
            Save();
        }
    }

    private bool Load() {
        if(FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "message.json")) {
            JsonFileLoader<DZLMessageConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "message.json", this);
            return true;
        }
        return false;
    }

    private void Save() {
        CheckDZLConfigPath();
        JsonFileLoader<DZLMessageConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "message.json", this);
    }
}
