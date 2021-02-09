class DZLHouseDefinition {
	
   	string houseType;
    int sellPrice;
    int buyPrice;
	ref array<vector> storagePosition;
	float storageBuyFactor;
	ref array<string> raidTools;

	
    void DZLHouseDefinition(string houseType, int buyPrice, int sellPrice, ref array<vector> storagePosition, float storageBuyFactor) {
        this.houseType = houseType;
        this.sellPrice = sellPrice;
        this.buyPrice = buyPrice;
        this.storagePosition = storagePosition;
        this.storageBuyFactor = storageBuyFactor;

        raidTools = new array<string>;
        raidTools.Insert("Crowbar");
    }

    int GetMaxStorage() {
        return storagePosition.Count();
    }
}
