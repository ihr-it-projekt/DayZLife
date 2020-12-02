class DZLHouseAlarm : DZLHouseExtension
{
    void DZLHouseAlarm(string id, string type, string description, int price, int level, string message) {
        this.id = id;
        this.type = type;
        this.description = description;
        this.level = level;
        this.message = message;
        isHouseAlarm = true;
    }

    override string GetMessage(PlayerBase raider, DZLHouse house) {
        if (level == 1) {
            return message;
        } else if (level == 2) {
            return message + house.name;
        } else if (level == 3) {
            return message + house.name + "/" + raider.GetIdentity().GetName();
        }

        return "";
    }

}
