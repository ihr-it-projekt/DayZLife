class DZLTraderType: DZLIdModel {
    string type;
    [NonSerialized()]string displayName = "";
    int sellPrice;
    int buyPrice;
    ref array<string> attachments;
    bool usePlayerAsSpawnPoint;
    bool isCar;
    bool isStorageItem = false;
    int maxStorage = 0;
    int maxSellPrice;
    int maxBuyPrice;
    int reducePerTick;
    int tickLengthInMinutes;

    int CalculateDynamicBuyPrice(DZLTraderTypeStorage currentStorage) {
        if(false == isStorageItem || buyPrice <= 0 || !currentStorage) return buyPrice;
        int storage = currentStorage.getStorage();

        return Math.Round(maxBuyPrice - ((storage / maxStorage) * (maxBuyPrice - buyPrice)));
    }

    int CalculateDynamicSellPrice(DZLTraderTypeStorage currentStorage) {
        if(false == isStorageItem || sellPrice <= 0 || !currentStorage) return sellPrice;
        int storage = currentStorage.getStorage();

        return Math.Round(maxSellPrice - ((storage / maxStorage) * (maxSellPrice - sellPrice)));
    }

    string GetStorageString(DZLTraderTypeStorage currentStorage) {
        string storage = "#unlimited";
        if(isStorageItem && currentStorage) {
            storage = currentStorage.getStorage().ToString() + "/" + maxStorage.ToString();
        }

        return storage;
    }

}