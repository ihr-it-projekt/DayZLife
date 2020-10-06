class DZLHouseDefinition {
	
    vector spawnPositionDiffStorage;
    vector spawnPositionMenu;
    string houseType;
    int sellPrice;
    int buyPrice;
	int countStorage;
	ref array<vector> storagePosition;

	
    void DZLHouseDefinition(vector spawnPositionDiffStorage, vector spawnPositionMenu, string houseType, int buyPrice, int sellPrice, int countStorag, ref array<vector> storagePosition) {
        this.spawnPositionDiffStorage = spawnPositionDiffStorage;
        this.spawnPositionMenu = spawnPositionMenu;
        this.houseType = houseType;
        this.sellPrice = sellPrice;
        this.buyPrice = buyPrice;
        this.countStorage = countStorage;
        this.storagePosition = storagePosition;
    }

}