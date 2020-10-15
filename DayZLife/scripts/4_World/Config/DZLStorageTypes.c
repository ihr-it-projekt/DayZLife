class DZLStorageTypes
{
    ref array<ref DZLStorageType> storageTypes;

    void DZLStorageTypes() {
        if (!Load()) {
            storageTypes = new array<ref DZLStorageType>;

            storageTypes.Insert(new DZLStorageType("SeaChest", 5, 100));
            storageTypes.Insert(new DZLStorageType("SeaChest", 50, 200));
        }
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "house.json")) {
            JsonFileLoader<DZLStorageTypes>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "storageTypes.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLStorageTypes>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "storageTypes.json", this);
        }
    }
}