class DZLLicenceCraftItemCollection {
    ref array<ref DZLLicenceCraftItem> collection;

    void DZLLicenceCraftItemCollection() {
        collection = new array<ref DZLLicenceCraftItem>
    }

    map<string, int> GetTypeCountMap() {
        map<string, int> mapCraft = new map<string, int>;
        foreach(DZLLicenceCraftItem item: collection) {
            int count = 0;
            if(!mapCraft.Find(item.GetLowerCaseType(), count)) {
                mapCraft.Insert(item.GetLowerCaseType(), item.quantity);
            } else {
                mapCraft.Set(item.GetLowerCaseType(), count + item.quantity);
            }
        }

        return mapCraft;
    }
}