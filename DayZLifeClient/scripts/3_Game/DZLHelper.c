static void LogMessageDZL(string message) {
    int hour;
    int minute;
    int second;
    int inSeconds;

    GetHourMinuteSecondUTC(hour, minute, second);
    Print("[DayZLife] " + hour.ToString() + ":" + minute.ToString() + ":" + second.ToString() + ": " + message);
    GetGame().AdminLog("[DayZLife] " + hour.ToString() + ":" + minute.ToString() + ":" + second.ToString() + ": " + message);
}

static void CheckDZLBasePath() {
    if(!FileExist(DAY_Z_LIFE_SERVER_FOLDER_BASE)) {
        MakeDirectory(DAY_Z_LIFE_SERVER_FOLDER_BASE);
    }
}

static void CheckDZLDataPath() {
    CheckDZLBasePath();
    if(!FileExist(DAY_Z_LIFE_SERVER_FOLDER_BASE_DATA)) {
        MakeDirectory(DAY_Z_LIFE_SERVER_FOLDER_BASE_DATA);
    }
    if(!FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA)) {
        MakeDirectory(DAY_Z_LIFE_SERVER_FOLDER_DATA);
    }
    if(!FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_ITEM_STORAGE)) {
        MakeDirectory(DAY_Z_LIFE_SERVER_FOLDER_DATA_ITEM_STORAGE);
    }
    if(!FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER)) {
        MakeDirectory(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER);
    }
    if(!FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_CAR)) {
        MakeDirectory(DAY_Z_LIFE_SERVER_FOLDER_DATA_CAR);
    }
    if(!FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_FRACTION)) {
        MakeDirectory(DAY_Z_LIFE_SERVER_FOLDER_DATA_FRACTION);
    }
    if(!FileExist(DAY_Z_LIFE_LOGS)) {
        MakeDirectory(DAY_Z_LIFE_LOGS);
    }
}
static void CheckDZLConfigPath() {
    CheckDZLBasePath();
    if(!FileExist(DAY_Z_LIFE_SERVER_FOLDER_BASE_CONFIG)) {
        MakeDirectory(DAY_Z_LIFE_SERVER_FOLDER_BASE_CONFIG);
    }
    if(!FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG)) {
        MakeDirectory(DAY_Z_LIFE_SERVER_FOLDER_CONFIG);
    }
}

static void CheckDZLDataSubPath(string path) {
    if(!FileExist(path)) {
        MakeDirectory(path);
    }
}

