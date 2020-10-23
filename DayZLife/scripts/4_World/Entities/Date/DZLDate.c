class DZLDate
{
	static const int HOUR_IN_SECONDS = 3600;
	static const int MINUTE_IN_SECONDS = 60;
	
	int hour;
    int minute;
    int second;
	int inSeconds;
	
	void DZLDate() {
		GetHourMinuteSecondUTC(hour, minute, second);
		inSeconds = hour * HOUR_IN_SECONDS + minute * MINUTE_IN_SECONDS + second;
	}

}