static void DebugMessageServerDZL(string message) {
	if (DAY_Z_LIFE_SERVER_DEBUG) {
		int hour;
	    int minute;
	    int second;
		int inSeconds;

		GetHourMinuteSecondUTC(hour, minute, second);
		Print("[DayZLifeServer DEBUG] " + hour.ToString() + ":" + minute.ToString() + ":" + second.ToString() + ": " + message);
        GetGame().AdminLog("[DayZLifeServer DEBUG] " + hour.ToString() + ":" + minute.ToString() + ":" + second.ToString() + ": " + message);
    }
}

static void CheckDLBasePath() {
    if (!FileExist(DAY_Z_LIFE_SERVER_FOLDER_BASE)) {
        MakeDirectory(DAY_Z_LIFE_SERVER_FOLDER_BASE);
    }
}

static void CheckDLDataPath() {
    CheckDLBasePath();
    if (!FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA)) {
        MakeDirectory(DAY_Z_LIFE_SERVER_FOLDER_DATA);
    }
}
static void CheckDLConfigPath() {
    CheckDLBasePath();
    if (!FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG)) {
        MakeDirectory(DAY_Z_LIFE_SERVER_FOLDER_CONFIG);
    }
}

static void CheckDLDataSubPath(string path) {
    CheckDLBasePath();
    CheckDLDataPath();
    if (!FileExist(path)) {
        MakeDirectory(path);
    }
}