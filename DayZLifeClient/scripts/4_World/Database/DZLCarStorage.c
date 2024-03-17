class DZLCarStorage: DZLFileSerializer {
    ref array<ref DZLCarStoreItem> items = new array<ref DZLCarStoreItem>;

    DZLCarStoreItem GetById(string id) {
        foreach(DZLCarStoreItem item: items) {
            if(item.GetId() == id) {
                return item;
            }
        }

        return null;
    }

}
