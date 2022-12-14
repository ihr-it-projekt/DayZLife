
static void LogMessageTBM(string message) {
    int hour;
    int minute;
    int second;
    int inSeconds;

    GetHourMinuteSecondUTC(hour, minute, second);
    Print("[DayZLife] " + hour.ToString() + ":" + minute.ToString() + ":" + second.ToString() + ": " + message);
    GetGame().AdminLog("[DayZLife] " + hour.ToString() + ":" + minute.ToString() + ":" + second.ToString() + ": " + message);
}

static void CheckTBMBasePath() {
    if (!FileExist(DAY_Z_LIFE_SERVER_FOLDER_BASE)) {
        MakeDirectory(DAY_Z_LIFE_SERVER_FOLDER_BASE);
    }
}

static void CheckTBMDataPath() {
    CheckTBMBasePath();
    if (!FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA)) {
        MakeDirectory(DAY_Z_LIFE_SERVER_FOLDER_DATA);
    }
}
static void CheckTBMConfigPath() {
    CheckTBMBasePath();
    if (!FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG)) {
        MakeDirectory(DAY_Z_LIFE_SERVER_FOLDER_CONFIG);
    }
}

static void CheckTBMDataSubPath(string path) {
    CheckTBMBasePath();
    CheckTBMDataPath();
    if (!FileExist(path)) {
        MakeDirectory(path);
    }
}


