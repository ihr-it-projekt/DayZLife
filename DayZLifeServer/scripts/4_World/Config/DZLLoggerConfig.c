class DZLLoggerConfig {
    static ref DZLLoggerConfig loggerConfig;
    string version = "2";
    bool logMoneyTransfer = true;
    bool logTraderTransactions = true;
    bool logCrafting = true;
    bool logLoadOut = true;
    bool logRaid = true;
    bool logStore = true;
    bool logArrest = true;
    bool logTicket = true;

    static DZLLoggerConfig Get() {
        if(!loggerConfig) {
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
            Save();
        }

        if("1" == version) {
            version = "2";
            logTicket = true;
            Save();
        }
    }

    private bool Load() {
        if(FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "logger.json")) {
            JsonFileLoader<DZLLoggerConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "logger.json", this);
            return true;
        }
        return false;
    }

    private void Save() {
        CheckDZLConfigPath();
        JsonFileLoader<DZLLoggerConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "logger.json", this);
    }
}
