class DZLLicenceToolItemCollection: array<ref DZLLicenceToolItem>
{
    map<string, int> GetTypeCountMap() {
        map<string, int> mapCraft = new map<string, int>;
        foreach(DZLLicenceToolItem item: this) {
            mapCraft.Insert(item.GetLowerCaseType(), item.quantity);
        }

        return mapCraft;
    }
}