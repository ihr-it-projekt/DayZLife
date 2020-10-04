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