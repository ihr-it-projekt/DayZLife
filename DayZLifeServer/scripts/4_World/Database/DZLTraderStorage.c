modded class DZLTraderStorage {
    void Insert(DZLTraderType item) {
        DZLTraderTypeStorage type = new DZLTraderTypeStorage(item);
        storageArray.Insert(type);
        storageMap.Set(type.GetType(), type);
    }
}