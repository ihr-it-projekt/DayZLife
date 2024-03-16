class DZLTraderStorage {
    private ref array<ref DZLTraderTypeStorage> storage = new array<ref DZLTraderTypeStorage>();

    void Insert(DZLTraderType item) {
        storage.Insert(new DZLTraderTypeStorage(item));
        Print(storage);
        Print(storage.Count());

    }

    ref array<ref DZLTraderTypeStorage> GetStorageItems() {
        Print(storage);
        Print(storage.Count());
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