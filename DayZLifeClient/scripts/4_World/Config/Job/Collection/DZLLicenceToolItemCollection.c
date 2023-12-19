class DZLLicenceToolItemCollection {
    ref array<ref DZLLicenceToolItem> collection;

    void DZLLicenceToolItemCollection() {
        collection = new array<ref DZLLicenceToolItem>
    }

    map<string, int> GetTypeCountMap() {
        map<string, int> mapCraft = new map<string, int>;
        foreach(DZLLicenceToolItem item: collection) {
            int count = 0;
            if (!mapCraft.Find(item.GetLowerCaseType(), count)) {
                mapCraft.Insert(item.GetLowerCaseType(), item.quantity);
            } else {
                mapCraft.Set(item.GetLowerCaseType(), count + item.quantity);
            }
        }

        return mapCraft;
    }
}