class DZLHouseExtension : DZLIdModel
{
    bool isStorage = false;
    string type;
    string description = "";
    int price;

    bool isHouseAlarm = false;
    string message = "";
    int level;
	
	string GetMessage(PlayerBase raider, DZLHouse house) {
		return message;
	}

}
