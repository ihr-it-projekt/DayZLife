static void DebugMessageServerDZL(string message) {
	if (DAY_Z_LIFE_SERVER_DEBUG) {
		int hour;
	    int minute;
	    int second;
		int inSeconds;

		GetHourMinuteSecondUTC(hour, minute, second);
		Print("[DayZLife DEBUG] " + hour.ToString() + ":" + minute.ToString() + ":" + second.ToString() + ": " + message);
        GetGame().AdminLog("[DayZLife DEBUG] " + hour.ToString() + ":" + minute.ToString() + ":" + second.ToString() + ": " + message);
    }
}

static void CheckBasePath() {
    if (!FileExist(DAY_Z_LIFE_SERVER_FOLDER_BASE)) {
        MakeDirectory(DAY_Z_LIFE_SERVER_FOLDER_BASE);
    }
}

static void CheckPath(string name) {
    CheckBasePath();
    if (!FileExist(name)) {
        MakeDirectory(name);
    }
}