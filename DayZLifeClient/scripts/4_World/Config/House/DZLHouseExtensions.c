class DZLHouseExtensions
{
    string version = "3";
    ref array<ref DZLHouseExtension> extensions;
    int pricePerLevelHouseInventory = 5000;

    void DZLHouseExtensions() {
        if (!Load()) {
            version = "3";
            extensions = new array<ref DZLHouseExtension>;
            extensions.Insert(new DZLHouseAlarm("4", "#Alarm_system", "#Alarm_system_desc_1", 10000, 1, "#Alarm_system_message_1"));
            extensions.Insert(new DZLHouseAlarm("5", "#Alarm_system", "#Alarm_system_desc_2", 20000, 2, "#Alarm_system_message_2"));
            extensions.Insert(new DZLHouseAlarm("6", "#Alarm_system", "#Alarm_system_desc_3", 40000, 3, "#Alarm_system_message_3"));
            extensions.Insert(new DZLHouseAlarm("7", "#Alarm_system", "#Alarm_system_desc_4", 50000, 4, "#Alarm_system_message_4"));
            extensions.Insert(new DZLInventoryExtension("70", "#desc_house_inventory", pricePerLevelHouseInventory));
            Save();
        }

        if ("2" == version) {
            version = "3";
            extensions.Insert(new DZLHouseAlarm("7", "#Alarm_system", "#Alarm_system_desc_4", 50000, 4, "#Alarm_system_message_4"));
            Save();
        }

        if ("3" == version) {
            version = "4";
            Save();
        }
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "houseExtensions.json")) {
            JsonFileLoader<DZLHouseExtensions>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "houseExtensions.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLHouseExtensions>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "houseExtensions.json", this);
        }
    }
}
