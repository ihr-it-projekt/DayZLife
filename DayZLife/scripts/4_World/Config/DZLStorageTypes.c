class DZLStorageTypes
{
    ref array<ref DZLStorageType> storageTypes;

    void DZLStorageTypes() {
        storageTypes = new array<ref DZLStorageType>;

        storageTypes.Insert(new DZLStorageType("DZL_Wooden_Crate_1", 50, 50));
        storageTypes.Insert(new DZLStorageType("DZL_Wooden_Crate_3", 150, 150));
        storageTypes.Insert(new DZLStorageType("DZL_Wooden_Crate_5", 250, 250));
    }
}