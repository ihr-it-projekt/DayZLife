class DZLHouseDefinition {
	
   string houseType;
    int sellPrice;
    int buyPrice;
	ref array<vector> storagePosition;
	float storageBuyFactor;

	
    void DZLHouseDefinition(string houseType, int buyPrice, int sellPrice, ref array<vector> storagePosition, float storageBuyFactor) {
        this.houseType = houseType;
        this.sellPrice = sellPrice;
        this.buyPrice = buyPrice;
        this.storagePosition = storagePosition;
        this.storageBuyFactor = storageBuyFactor;
    }

    int GetMaxStorage() {
        return storagePosition.Count();
    }
	
}