class DZLCarStorage: DZLFileSerializer {
    ref array<ref DZLCarStoreItem> items = new array<ref DZLCarStoreItem>;

    void DZLCarStorage(string playerId) {}
    void Add(CarScript entity, vector storagePosition, bool withCargo, bool isInsuranceCase) {};
    void AddDZLCarStoreItem(DZLCarStoreItem carStoreItem) {};

    DZLCarStoreItem GetById(string id) {
        foreach(DZLCarStoreItem item: items) {
            if(item.GetId() == id) {
                return item;
            }
        }

        return null;
    }

}
