class DZLHouseExtensions
{
    ref array<ref DZLHouseExtension> extensions;

    void DZLStorageTypes() {
        extensions = new array<ref DZLHouseExtension>;

        extensions.Insert(new DZLStorageType("DZL_Wooden_Crate_1", "#desc_storage_1", 50));
        extensions.Insert(new DZLStorageType("DZL_Wooden_Crate_3", "#desc_storage_2", 150));
        extensions.Insert(new DZLStorageType("DZL_Wooden_Crate_5", "#desc_storage_3", 250));

        extensions.Insert(new DZLHouseAlarm("#Alarm_system", "#Alarm_system_desc_1", 1250, 1, "#Alarm_system_message_1"));
        extensions.Insert(new DZLHouseAlarm("#Alarm_system", "#Alarm_system_desc_2", 2500, 2, "#Alarm_system_message_2"));
        extensions.Insert(new DZLHouseAlarm("#Alarm_system", "#Alarm_system_desc_3", 5000, 3, "#Alarm_system_message_3"));
        extensions.Insert(new DZLHouseAlarm("#Alarm_system", "#Alarm_system_desc_4", 10000, 4, "#Alarm_system_message_4"));
    }
}
