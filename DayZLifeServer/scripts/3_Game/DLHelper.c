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

