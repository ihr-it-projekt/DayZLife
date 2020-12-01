class DZLHouseExtensions
{
    ref array<ref DZLHouseExtension> extensions;

    void DZLHouseExtensions() {
        extensions = new array<ref DZLHouseExtension>;
        extensions.Insert(new DZLStorageType("1", "DZL_Wooden_Crate_1", "#desc_storage_1", 50));
        extensions.Insert(new DZLStorageType("2", "DZL_Wooden_Crate_3", "#desc_storage_2", 150));
        extensions.Insert(new DZLStorageType("3", "DZL_Wooden_Crate_5", "#desc_storage_3", 250));
        extensions.Insert(new DZLHouseAlarm("4", "#Alarm_system", "#Alarm_system_desc_1", 1250, 1, "#Alarm_system_message_1"));
        extensions.Insert(new DZLHouseAlarm("5", "#Alarm_system", "#Alarm_system_desc_2", 2500, 2, "#Alarm_system_message_2"));
        extensions.Insert(new DZLHouseAlarm("6", "#Alarm_system", "#Alarm_system_desc_3", 5000, 3, "#Alarm_system_message_3"));
    }
}
