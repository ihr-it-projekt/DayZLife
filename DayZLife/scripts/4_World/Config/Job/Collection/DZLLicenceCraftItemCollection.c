class DZLLicenceCraftItemCollection: array<ref DZLLicenceCraftItem>
{
    map<string, int> GetTypeCountMap() {
        map<string, int> mapCraft = new map<string, int>;
        foreach(DZLLicenceCraftItem craftItem: this) {
            mapCraft.Insert(craftItem.GetLowerCaseType(), craftItem.quantity);
        }

        return mapCraft;
    }
}