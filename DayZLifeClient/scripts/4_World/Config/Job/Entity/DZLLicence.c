class DZLLicence: DZLIdModel {
    int price;
    string name;
    vector position;
    int range;
    string dependencyLicence;
    ref DZLLicenceCraftedItem craftedItem;
    ref DZLLicenceCraftItemCollection craftItems;
    ref DZLLicenceToolItemCollection toolItems;
    int durationForCrafting;


    void DZLLicence(int _price, string _name, vector _position, string _dependencyLicence, ref DZLLicenceCraftedItem _craftedItem, int _durationForCrafting, DZLLicenceToolItemCollection _toolItems, DZLLicenceCraftItemCollection _craftItems) {
        this.price = _price;
        this.name = _name;
        this.position = _position;
        this.dependencyLicence = _dependencyLicence;
        this.craftedItem = _craftedItem;
        this.durationForCrafting = _durationForCrafting;
        this.toolItems = _toolItems;
        this.craftItems = _craftItems;

        SetId();
    }
}
