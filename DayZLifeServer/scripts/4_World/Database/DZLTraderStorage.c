modded class DZLTraderStorage {
    void Insert(DZLTraderType item) {
        DZLTraderTypeStorage type = new DZLTraderTypeStorage(item);
        if (!storageArray) storageArray = new array<ref DZLTraderTypeStorage>;
        storageArray.Insert(type);
        if (!storageMap) storageMap = new map<string, ref DZLTraderTypeStorage>;
        storageMap.Set(type.GetType(), type);
    }
}