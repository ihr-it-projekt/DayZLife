class DZLLicenceToolItemCollection {
    ref array<ref DZLLicenceToolItem> collection = new array<ref DZLLicenceToolItem>;

    map<string, ref DZLFoundLicenseCraftItems> GetLicenceCraftItems() {
        map<string, ref DZLFoundLicenseCraftItems> mapCraft = new map<string, ref DZLFoundLicenseCraftItems>;
        foreach(DZLLicenceCraftItem item: collection) {
            DZLFoundLicenseCraftItems foundItems;
            string key = item.GetKey();
            if(!mapCraft.Find(key, foundItems)) {
                foundItems = new DZLFoundLicenseCraftItems(item.type, item.quantity, item.health, item.healthReduce);
                mapCraft.Insert(key, foundItems);
                continue;
            }
            foundItems.foundQuantity += item.quantity;
        }

        return mapCraft;
    }
}