class DZLHouseExtensions
{
    string version = "2";
    ref array<ref DZLHouseExtension> extensions;
    int pricePerLevelHouseInventory = 5000;
    int inventoryItemsPerLevel = 10;
    int maxHouseInventoryLevel = 20;

    void DZLHouseExtensions() {
        if (!Load()) {
            version = "2";
            extensions = new array<ref DZLHouseExtension>;
            extensions.Insert(new DZLStorageType("1", "DZL_Wooden_Crate_1", "#desc_storage_1", 15000));
            extensions.Insert(new DZLStorageType("2", "DZL_Wooden_Crate_3", "#desc_storage_2", 30000));
            extensions.Insert(new DZLStorageType("3", "DZL_Wooden_Crate_5", "#desc_storage_3", 60000));
            extensions.Insert(new DZLHouseAlarm("4", "#Alarm_system", "#Alarm_system_desc_1", 10000, 1, "#Alarm_system_message_1"));
            extensions.Insert(new DZLHouseAlarm("5", "#Alarm_system", "#Alarm_system_desc_2", 20000, 2, "#Alarm_system_message_2"));
            extensions.Insert(new DZLHouseAlarm("6", "#Alarm_system", "#Alarm_system_desc_3", 40000, 3, "#Alarm_system_message_3"));
            extensions.Insert(new DZLInventoryExtension("70", "#desc_house_inventory", pricePerLevelHouseInventory, inventoryItemsPerLevel));
            Save();
        }

        if (version == "1") {
            extensions.Insert(new DZLInventoryExtension("70", "#desc_house_inventory", pricePerLevelHouseInventory, inventoryItemsPerLevel));
            pricePerLevelHouseInventory = 5000;
            inventoryItemsPerLevel = 10;
            maxHouseInventoryLevel = 500;
            version = "2";
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
