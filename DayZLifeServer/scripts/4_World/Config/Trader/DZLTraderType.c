modded class DZLTraderType: DZLIdModel {

    void DZLTraderType(string _type, int _sellPrice, int _buyPrice, array<string> _attachments, bool _usePlayerAsSpawnPoint = true, bool _isCar = false) {
        this.type = _type;
        this.sellPrice = _sellPrice;
        this.buyPrice = _buyPrice;
        this.attachments = _attachments;
        this.usePlayerAsSpawnPoint = _usePlayerAsSpawnPoint;
        this.isCar = _isCar;
        SetId();
    }
}