modded class DZLCrimeConfig {
    private string version = "1";
    int maxMoneyPerTick = 30;
    int minMoneyPerTick = 3;
    int maxMoneyPerRob = 100000;
    ref array<string> robTools;
    bool raidIsCopControlled = false;
    bool raidTimeControlled = false;
    int minCountCopsForRaid = 5;
    int raidStartTimeHour = 16;
    int raidEndTimeHour = 22;
    int raidStartTimeMinute = 0;
    int raidEndTimeMinute = 59;
    int raidDurationTickInSeconds = 60;
    int maxRaidDurationInSeconds = 6000;
    float copAlarmFactorForCopMessage = 0.95;
    int raidCoolDownTimeInSeconds = 1800;
    bool canStartRaidIfBankRaidRuns = false;
    ref array<ref DZLCrimePosition> shopPosition;

    void DZLCrimeConfig() {
        if(!Load()) {
            robTools = new array<string>;
            robTools.Insert("Deagle");
            shopPosition = new array<ref DZLCrimePosition>;
            shopPosition.Insert(new DZLCrimePosition("6873.430176 8.302020 3093.559082", "135.000015 0.000000 0.000000"));
            Save();
        }
    }

    private bool Load() {
        if(FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "CrimeConfig.json")) {
            JsonFileLoader<DZLCrimeConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "CrimeConfig.json", this);
            return true;
        }
        return false;
    }

    private void Save() {
            CheckDZLConfigPath();
            JsonFileLoader<DZLCrimeConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "CrimeConfig.json", this);
    }
}