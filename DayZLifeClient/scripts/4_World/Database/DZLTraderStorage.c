class DZLTraderStorage {
    private ref array<ref DZLTraderTypeStorage> storage = new array<ref DZLTraderTypeStorage>();

    ref array<ref DZLTraderTypeStorage> GetStorageItems() {
        return storage;
    }

    DZLTraderTypeStorage GetCurrentStorageByName(string name) {
        foreach(DZLTraderTypeStorage itemStorage: storage) {
            if(name == itemStorage.GetType()) {
                return itemStorage;
            }
        }

        return null;
    }
}