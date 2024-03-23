modded class DZLCraftLicence {


    void DZLCraftLicence(int _price, string _name, vector _position, string _dependencyLicence, ref DZLLicenceCraftedItem _craftedItem, int _durationForCrafting, DZLLicenceToolItemCollection _toolItems, DZLLicenceCraftItemCollection _craftItems) {
        this.price = _price;
        this.name = _name;
        this.position = _position;
        this.dependencyLicence = _dependencyLicence;
        this.craftedItem = _craftedItem;
        this.durationForCrafting = _durationForCrafting;
        this.toolItems = _toolItems;
        this.craftItems = _craftItems;
        this.showNotOnMapInAlmanac = false;

        SetId();
    }
}
