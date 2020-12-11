class DZLHouseExtension : DZLIdModel
{
    bool isStorage = false;
    string type;
    string description = "";
    int price;

    bool isHouseAlarm = false;
    string message = "";
    int level;
	
	string GetMessage(PlayerBase raider, string name) {
        if (level == 1) {
            return message;
        } else if (level == 2) {
            return message + " " + name;
        } else if (level == 3) {
            return message + " " + name + " / " + raider.GetIdentity().GetName();
        }

		return message;
	}

}
