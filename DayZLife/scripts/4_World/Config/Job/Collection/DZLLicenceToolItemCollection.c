class DZLLicenceToolItemCollection
{
    ref array<ref DZLLicenceToolItem> collection;

    void DZLLicenceToolItemCollection() {
        collection = new array<ref DZLLicenceToolItem>
    }

    map<string, int> GetTypeCountMap() {
        map<string, int> mapCraft = new map<string, int>;
        foreach(DZLLicenceToolItem item: collection) {
            mapCraft.Insert(item.GetLowerCaseType(), item.quantity);
        }

        return mapCraft;
    }
}