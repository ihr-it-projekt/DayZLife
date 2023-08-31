class DZLHouseExtension : DZLIdModel
{
    bool isStorage = false;
    string type;
    string description = "";
    int price;

    bool isHouseAlarm = false;
    bool isHouseInventory = false;
    string message = "";
    string copMessage = "#cop_message_house_alarm";
    int level;
	
	string GetMessage(PlayerBase raider, string name) {
        if (level == 1) {
            return message;
        } else if (level == 2) {
            return message + " " + name;
        } else if (level == 3 || level == 4) {
            return message + " " + name + " / " + raider.GetIdentity().GetName();
        }

		return message;
	}
	
	string GetCopMessage() {
		return copMessage;
	}

}
