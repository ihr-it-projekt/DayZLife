class DZLTraderType
{
    string type;
    string displayName = "";
    int sellPrice;
    int buyPrice;

    void DZLTraderType(string type, int sellPrice, int buyPrice) {
        this.type = type;
        this.sellPrice = sellPrice;
        this.buyPrice = buyPrice;
    }
}