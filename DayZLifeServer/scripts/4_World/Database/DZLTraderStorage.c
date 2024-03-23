modded class DZLTraderStorage {
    void Insert(DZLTraderType item) {
        storage.Insert(new DZLTraderTypeStorage(item));
    }
}