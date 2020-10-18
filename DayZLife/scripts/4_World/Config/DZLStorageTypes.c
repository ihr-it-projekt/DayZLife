class DZLStorageTypes
{
    ref array<ref DZLStorageType> storageTypes;

    void DZLStorageTypes() {
        storageTypes = new array<ref DZLStorageType>;

        storageTypes.Insert(new DZLStorageType("SeaChest", 5, 100));
        storageTypes.Insert(new DZLStorageType("SeaChest", 50, 200));
    }
}