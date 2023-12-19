class DZLMessageConfig {
    string version = "1";
    bool mustHavePersonalRadio = true;
    bool radioMustHaveBattery = true;
    bool showOnlinePlayersInMessageMenu = true;

    void DZLMessageConfig() {
        if(!Load()) {
            version = "1";
            mustHavePersonalRadio = true;
            radioMustHaveBattery = true;
            showOnlinePlayersInMessageMenu = true;
            Save();
        }
    }

    private bool Load() {
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "message.json")) {
            JsonFileLoader<DZLMessageConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "message.json", this);
            return true;
        }
        return false;
    }

    private void Save() {
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLMessageConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "message.json", this);
        }
    }
}
