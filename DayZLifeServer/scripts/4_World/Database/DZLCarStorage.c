modded class DZLCarStorage {

    void DZLCarStorage(string playerId) {
        Init(DAY_Z_LIFE_SERVER_FOLDER_DATA_CAR, "car_" + playerId);

        if(LoadJSON("car_" + playerId + ".json")) {
            Init(DAY_Z_LIFE_SERVER_FOLDER_DATA_CAR, "car_" + playerId);
            Save();
        }

        Init(DAY_Z_LIFE_SERVER_FOLDER_DATA_CAR, "car_" + playerId);
        Load();
    }

    void Add(CarScript entity, vector storagePosition, bool withCargo, bool isInsuranceCase) {
        AddDZLCarStoreItem(new DZLCarStoreItem(entity, storagePosition, withCargo, isInsuranceCase));
    }

    void AddDZLCarStoreItem(DZLCarStoreItem carStoreItem) {
        items.Insert(carStoreItem);
        Save();
    }

    void RemoveItem(DZLCarStoreItem item) {
        items.RemoveItem(item);
        Save();
    }

    override protected bool Read(FileSerializer ctx) {
        if(!ctx.Read(items)) return false;
        return true;
    }

    override protected void Write(FileSerializer ctx) {
        ctx.Write(items);
    }

    private bool LoadJSON(string tmpFileName) {
        if(FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_CAR + tmpFileName)) {
            JsonFileLoader<DZLCarStorage>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_CAR + tmpFileName, this);
            DeleteFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_CAR + tmpFileName);
            return true;
        }
        return false;
    }

}
