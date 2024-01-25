class DZLCarStorage {
    string fileName = "";
    ref array<ref DZLCarStoreItem> items;

    void DZLCarStorage(string playerId) {
        fileName = "car_" + playerId + ".json";
        if(!Load()) {
            items = new array<ref DZLCarStoreItem>;
            Save();
        }
    }

    void Add(CarScript entity, vector storagePosition, bool withCargo, bool isInsuranceCase) {
        AddDZLCarStoreItem(new DZLCarStoreItem(entity, storagePosition, withCargo, isInsuranceCase));
    }

    void AddDZLCarStoreItem(DZLCarStoreItem carStoreItem) {
        items.Insert(carStoreItem);
        Save();
    }

    DZLCarStoreItem GetById(string id) {
        foreach(DZLCarStoreItem item: items) {
            if(item.GetId() == id) {
                return item;
            }
        }

        return null;
    }

    void RemoveItem(DZLCarStoreItem item) {
        items.RemoveItem(item);
        Save();
    }

    private bool Load() {
        if(GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_CAR + fileName)) {
            JsonFileLoader<DZLCarStorage>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_CAR + fileName, this);
            return true;
        }
        return false;
    }

    private bool Save() {
        if(GetGame().IsServer()) {
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_CAR);
            DZLJsonFileHandler<DZLCarStorage>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_CAR + fileName, this);
            return true;
        }
        return false;
    }
}
