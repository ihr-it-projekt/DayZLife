class DZLTraderStorage {
    private ref array<ref DZLTraderTypeStorage> storageArray = new array<ref DZLTraderTypeStorage>();
    [NonSerialized()] private ref map<string, ref DZLTraderTypeStorage> storageMap;

    array<ref DZLTraderTypeStorage> GetStorageItems() {
        return storageArray;
    }

    private void LoadStorageMap() {
        storageMap = new map<string, ref DZLTraderTypeStorage>();

        foreach(DZLTraderTypeStorage itemStorage: storageArray) {
            storageMap.Insert(itemStorage.GetType(), itemStorage);
        }
    }

    DZLTraderTypeStorage GetCurrentStorageByName(string name) {
        if(!storageMap || storageMap.Count() == 0) LoadStorageMap();

        if(storageMap.Contains(name)) {
            return storageMap.Get(name);
        }

        return null;
    }
}