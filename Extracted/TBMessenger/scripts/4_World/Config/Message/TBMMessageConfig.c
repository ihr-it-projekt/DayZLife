class TBMMessageConfig
{
	string version = "1";
    bool mustHavePersonalRadio = true;
    bool radioMustHaveBattery = true;
    bool showOnlinePlayersInMessageMenu = true;
    ref array<ref string> canSendToAll;

    void TBMMessageConfig() {
        if(!Load()) {
            version = "1";
            mustHavePersonalRadio = true;
            radioMustHaveBattery = true;
            showOnlinePlayersInMessageMenu = true;
            canSendToAll = new array<ref string>;
            Save();
        }
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "message.json")) {
            JsonFileLoader<TBMMessageConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "message.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckTBMConfigPath();
            JsonFileLoader<TBMMessageConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "message.json", this);
        }
    }
}
