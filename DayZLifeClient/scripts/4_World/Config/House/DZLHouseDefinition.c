class DZLHouseDefinition {

    string houseType;
    int sellPrice = 50000;
    int buyPrice = 100000;
    ref array<string> raidTools = {"Crowbar"};
    float storageBuyFactor = 10;
    int inventoryItemsPerLevel = 10;
    int maxHouseInventoryLevel = 20;

    void DZLHouseDefinition(string _houseType) {
        this.houseType = houseType;
    }

}
