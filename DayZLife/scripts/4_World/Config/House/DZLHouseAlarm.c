class DZLHouseAlarm : DZLHouseExtension
{
    int level;
    string message;

    void DZLHouseAlarm(string type, string description, int price, int level, string message) {
        this.type = type;
        this.description = description;
        this.level = level;
        this.message = message;
    }

}
