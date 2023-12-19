class DZLHouseAlarm : DZLHouseExtension {
    void DZLHouseAlarm(string id, string type, string description, int price, int level, string message) {
        this.id = id;
        this.type = type;
        this.description = description;
        this.price = price;
        this.level = level;
        this.message = message;
        isHouseAlarm = true;
    }
}
