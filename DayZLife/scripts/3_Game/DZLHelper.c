static void DebugMessageDZL(string message) {
	if (DAY_Z_LIFE_DEBUG) {
		int hour;
	    int minute;
	    int second;
		int inSeconds;

		GetHourMinuteSecondUTC(hour, minute, second);
		Print("[DayZLife DEBUG] " + hour.ToString() + ":" + minute.ToString() + ":" + second.ToString() + ": " + message);
        GetGame().AdminLog("[DayZLife DEBUG] " + hour.ToString() + ":" + minute.ToString() + ":" + second.ToString() + ": " + message);
    }
}

static void CheckDZLBasePath() {
    if (!FileExist(DAY_Z_LIFE_SERVER_FOLDER_BASE)) {
        MakeDirectory(DAY_Z_LIFE_SERVER_FOLDER_BASE);
    }
}

static void CheckDZLDataPath() {
    CheckDZLBasePath();
    if (!FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA)) {
        MakeDirectory(DAY_Z_LIFE_SERVER_FOLDER_DATA);
    }
}
static void CheckDZLConfigPath() {
    CheckDZLBasePath();
    if (!FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG)) {
        MakeDirectory(DAY_Z_LIFE_SERVER_FOLDER_CONFIG);
    }
}

static void CheckDZLDataSubPath(string path) {
    CheckDZLBasePath();
    CheckDZLDataPath();
    if (!FileExist(path)) {
        MakeDirectory(path);
    }
}