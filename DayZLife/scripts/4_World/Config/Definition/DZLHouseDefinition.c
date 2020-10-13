class DZLHouseDefinition {
	
   string houseType;
    int sellPrice;
    int buyPrice;
	int countMaxStorage;
	ref array<vector> storagePosition;

	
    void DZLHouseDefinition(string houseType, int buyPrice, int sellPrice, int countMaxStorage, ref array<vector> storagePosition) {
        this.houseType = houseType;
        this.sellPrice = sellPrice;
        this.buyPrice = buyPrice;
        this.countMaxStorage = countMaxStorage;
        this.storagePosition = storagePosition;
    }

}