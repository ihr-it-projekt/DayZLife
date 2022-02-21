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
	int currentStorage;

    void DZLTraderType(string type, int sellPrice, int buyPrice, array<string> attachments, bool usePlayerAsSpawnPoint = true, bool isCar = false) {
        this.type = type;
        this.sellPrice = sellPrice;
        this.buyPrice = buyPrice;
		this.attachments = attachments;
		this.usePlayerAsSpawnPoint = usePlayerAsSpawnPoint;
		this.isCar = isCar;
        SetId();
    }
    
    int CalculateDynamicSellPrice() {
        if (false == isStorageItem) {
            return sellPrice;
        }

        int maxAmountThatCanSell = maxStorage - currentStorage;

        if (maxAmountThatCanSell  < 1) {
            return 0;
        }

        float storageInPercent = (maxStorage - currentStorage) / maxStorage;
        float priceSpan = maxSellPrice - sellPrice;

        float price = priceSpan * storageInPercent;

        return price;
    }
    
    int CalculateDynamicBuyPrice() {
        if (false == isStorageItem) {
            return buyPrice;
        }

        int price = 0;

        if (currentStorage > 0) {
            float storageInPercent = (maxStorage - currentStorage) / maxStorage;
            float priceSpan = maxBuyPrice - buyPrice;
            price = priceSpan * storageInPercent;
        }

        return price;
    }

    void storageUp() {
        currentStorage++;
    }

    void storageDown() {
        currentStorage--;
    }

    string GetStorageString() {
        string storage = "#unlimited";
        if (isStorageItem) {
            storage = currentStorage.ToString() + "/" + maxStorage.ToString();
        }

        return storage;
    }
}