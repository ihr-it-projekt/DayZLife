class DZLLoggerConfig
{
    static ref DZLLoggerConfig loggerConfig;
	string version = "1";
	bool logMoneyTransfer = true;
	bool logTraderTransactions = true;
	bool logCrafting = true;
	bool logLoadOut = true;
	bool logRaid = true;
	bool logStore = true;
	bool logArrest = true;
	bool logHouseTrade = true;

    static DZLLoggerConfig Get() {
        if (!loggerConfig) {
            loggerConfig = new DZLLoggerConfig;
        }
        return loggerConfig;
    }

    void DZLLoggerConfig() {
        if(!Load()) {
            logMoneyTransfer = true;
            logTraderTransactions = true;
            logCrafting = true;
            logLoadOut = true;
            logRaid = true;
            logStore = true;
            logArrest = true;
            logHouseTrade = true;
            Save();
        }
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "logger.json")) {
            JsonFileLoader<DZLLoggerConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "logger.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLLoggerConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "logger.json", this);
        }
    }
}
