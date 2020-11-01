class DZLLicenceCraftItemCollection
{
    ref array<ref DZLLicenceCraftItem> collection;

    void DZLLicenceCraftItemCollection() {
        collection = new array<ref DZLLicenceCraftItem>
    }

    map<string, int> GetTypeCountMap() {
        map<string, int> mapCraft = new map<string, int>;
        foreach(DZLLicenceCraftItem craftItem: collection) {
            mapCraft.Insert(craftItem.GetLowerCaseType(), craftItem.quantity);
        }

        return mapCraft;
    }
}