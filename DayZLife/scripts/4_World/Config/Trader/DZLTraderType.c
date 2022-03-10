class DZLTraderType: DZLIdModel
{
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

    void DZLTraderType(string type, int sellPrice, int buyPrice, array<string> attachments, bool usePlayerAsSpawnPoint = true, bool isCar = false) {
        this.type = type;
        this.sellPrice = sellPrice;
        this.buyPrice = buyPrice;
		this.attachments = attachments;
		this.usePlayerAsSpawnPoint = usePlayerAsSpawnPoint;
		this.isCar = isCar;
        SetId();
    }
    
    int CalculateDynamicSellPrice(DZLTraderTypeStorage currentStorage, EntityAI item = null) {
        if (false == isStorageItem || sellPrice <= 0 || !currentStorage || !item) {
            return sellPrice;
        }

        int maxAmountThatCanSell = maxStorage - currentStorage.getStorage();

        if (maxAmountThatCanSell <= 0) {
            return 0;
        }

        float storageLeft = maxStorage - currentStorage.getStorage() + GetStorageAdd(item);
        float storageInPercent = storageLeft / maxStorage;
        float priceSpan = maxSellPrice - sellPrice;

        return  Math.Round(priceSpan * storageInPercent + sellPrice);
    }
    
    int CalculateDynamicBuyPrice(DZLTraderTypeStorage currentStorage) {
        if (false == isStorageItem || buyPrice <= 0 || !currentStorage) {
            return buyPrice;
        }

        int price = 0;

        if (currentStorage.getStorage() > 0) {
            float storageInPercent = (maxStorage - currentStorage.getStorage() - 1) / maxStorage;
            float priceSpan = maxBuyPrice - buyPrice;
            price = priceSpan * storageInPercent + buyPrice;
        }

        return price;
    }

    string GetStorageString(DZLTraderTypeStorage currentStorage) {
        string storage = "#unlimited";
        if (isStorageItem && currentStorage) {
            storage = currentStorage.getStorage().ToString() + "/" + maxStorage.ToString();
        }

        return storage;
    }

    float GetStorageAdd(EntityAI item = null) {
        int quantity = 1;
        int maxQuantity = 1;
        if (item) {
            maxQuantity = item.GetQuantityMax();
            quantity = item.GetQuantity();
        }

        if (quantity == 0) {
            quantity = 1;
            maxQuantity = 1;
        }

        return quantity/maxQuantity;
    }
}