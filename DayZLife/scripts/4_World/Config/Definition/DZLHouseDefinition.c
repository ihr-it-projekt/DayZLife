class DZLHouseDefinition {
	
    vector spawnPositionDiffStorage;
    vector spawnPositionMenu;
    string houseType;
    int price;

	
    void DZLHouseDefinition(vector spawnPositionDiffStorage, vector spawnPositionMenu, string houseType, int price) {
        this.spawnPositionDiffStorage = spawnPositionDiffStorage;
        this.spawnPositionMenu = spawnPositionMenu;
        this.houseType = houseType;
        this.price = price;
    }

}