class DZLTraderCategory {
    string name;
    ref array<ref DZLTraderType> items;
    [NonSerialized()] ref map<string, ref DZLTraderType> itemsIdMap;
    [NonSerialized()] ref map<string, ref DZLTraderType> itemsTypeMap;

    private void LoadItemsMap() {
        itemsIdMap = new map<string, ref DZLTraderType>();
        itemsTypeMap = new map<string, ref DZLTraderType>();
        foreach(DZLTraderType item: items) {
            itemsIdMap.Insert(item.GetId(), item);
            itemsTypeMap.Insert(item.type, item);
        }
    }

    DZLTraderType GetItemByType(string id) {
        if(!itemsTypeMap) LoadItemsMap();

        return itemsTypeMap.Get(id);
    }

    DZLTraderType GetItemById(string id) {
        if(!itemsIdMap) LoadItemsMap();

        return itemsIdMap.Get(id);
    }
}