class DZLTraderType: DZLIdModel
{
    string type;
    string displayName = "";
    int sellPrice;
    int buyPrice;
    ref array<string> attachments;
	bool usePlayerAsSpawnPoint;
	bool isCar;

    void DZLTraderType(string type, int sellPrice, int buyPrice, array<string> attachments, bool usePlayerAsSpawnPoint = true, bool isCar = false) {
        this.type = type;
        this.sellPrice = sellPrice;
        this.buyPrice = buyPrice;
		this.attachments = attachments;
		this.usePlayerAsSpawnPoint = usePlayerAsSpawnPoint;
		this.isCar = isCar;
        SetId();
    }
}