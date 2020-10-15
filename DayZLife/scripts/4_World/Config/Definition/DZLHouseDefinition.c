class DZLHouseDefinition {
	
   string houseType;
    int sellPrice;
    int buyPrice;
	ref array<vector> storagePosition;
	int storageBasePrice;
	float storageBuyFactor;

	
    void DZLHouseDefinition(string houseType, int buyPrice, int sellPrice, int countMaxStorage, ref array<vector> storagePosition, int storageBasePrice, float storageBuyFactor) {
        this.houseType = houseType;
        this.sellPrice = sellPrice;
        this.buyPrice = buyPrice;
        this.storagePosition = storagePosition;
        this.storageBasePrice = storageBasePrice;
        this.storageBuyFactor = storageBuyFactor;
    }

    int GetMaxStorage() {
        return storagePosition.Count();
    }

    int GetPriceForStorage(int numberOfStorage) {
        if (numberOfStorage > GetMaxStorage()) {
			numberOfStorage = GetMaxStorage();
		}

		return storageBasePrice * (numberOfStorage * storageBuyFactor);
    }

}