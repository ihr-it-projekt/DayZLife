class TBMDate
{
	static const int YEAR_IN_SECONDS = 31556952;
    static const int MONTH_IN_SECONDS = 2419200;
    static const int DAY_IN_SECONDS = 86400;
    static const int HOUR_IN_SECONDS = 3600;
    static const int MINUTE_IN_SECONDS = 60;

    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int inSeconds;

    void TBMDate() {
        GetYearMonthDay(year, month, day);
        GetHourMinuteSecondUTC(hour, minute, second);
        inSeconds = month * MONTH_IN_SECONDS + day * DAY_IN_SECONDS + hour * HOUR_IN_SECONDS + minute * MINUTE_IN_SECONDS + second;
    }

    string ToDateString() {
        return year.ToString() + "-" + month.ToString() + "-" + day.ToString() + " " + hour.ToString() + ":" + minute.ToString() + ":" + second.ToString();
    }
}
