class DZLTraderType: DZLIdModel {
    string type;
    string displayName = "";
    int sellPrice;
    int buyPrice;
    ref array<string> attachments;
    bool usePlayerAsSpawnPoint;
    bool isCar;
    bool isStorageItem = false;
    int maxStorage = 0;
    int maxBuyPrice;
    int maxSellPrice;
    int reducePerTick;
    int tickLengthInMinutes;

    void DZLTraderType(string _type, int _sellPrice, int _buyPrice, array<string> _attachments, bool _usePlayerAsSpawnPoint = true, bool _isCar = false) {
        this.type = _type;
        this.sellPrice = _sellPrice;
        this.buyPrice = _buyPrice;
        this.attachments = _attachments;
        this.usePlayerAsSpawnPoint = _usePlayerAsSpawnPoint;
        this.isCar = _isCar;
        SetId();
    }

    int CalculateDynamicSellPrice(DZLTraderTypeStorage currentStorage, EntityAI item = null) {
        if(false == isStorageItem || sellPrice <= 0 || !currentStorage) {
            return sellPrice;
        }

        int maxAmountThatCanSell = maxStorage - currentStorage.getStorage();

        if(maxAmountThatCanSell <= 0) {
            return 0;
        }

        float storageLeft = maxStorage - currentStorage.getStorage() + 1;
        float storageInPercent = storageLeft / maxStorage;
        float priceSpan = maxSellPrice - sellPrice;

        return Math.Round(priceSpan * storageInPercent + sellPrice);
    }

    int CalculateDynamicBuyPrice(DZLTraderTypeStorage currentStorage) {
        if(false == isStorageItem || buyPrice <= 0 || !currentStorage) {
            return buyPrice;
        }

        int price = 0;

        if(currentStorage.getStorage() > 0) {
            float storageInPercent = (maxStorage - currentStorage.getStorage() - 1) / maxStorage;
            float priceSpan = maxBuyPrice - buyPrice;
            price = priceSpan * storageInPercent + buyPrice;
        }

        return price;
    }

    string GetStorageString(DZLTraderTypeStorage currentStorage) {
        string storage = "#unlimited";
        if(isStorageItem && currentStorage) {
            storage = currentStorage.getStorage().ToString() + "/" + maxStorage.ToString();
        }

        return storage;
    }

}