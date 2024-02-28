class DZLLicenceToolItemCollection {
    ref array<ref DZLLicenceToolItem> collection;

    void DZLLicenceToolItemCollection() {
        collection = new array<ref DZLLicenceToolItem>
    }

    ref map<string, ref DZLFoundLicenseCraftItems> GetLicenceCraftItems() {
        map<string, ref DZLFoundLicenseCraftItems> mapCraft = new map<string, ref DZLFoundLicenseCraftItems>;
        foreach(DZLLicenceCraftItem item: collection) {
            DZLFoundLicenseCraftItems foundItems = new DZLFoundLicenseCraftItems(item.type, item.quantity, item.health);
            string key = item.GetKey();
            if(!mapCraft.Find(key, foundItems)) {
                mapCraft.Insert(key, foundItems);
                continue;
            }
            foundItems.quantity += item.quantity;
        }

        return mapCraft;
    }
}