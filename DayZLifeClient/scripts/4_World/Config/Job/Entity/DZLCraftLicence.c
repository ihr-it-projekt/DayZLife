class DZLCraftLicence: DZLIdModel {
    int price;
    string name;
    vector position;
    vector orientation = "0 0 0";
    string dependencyLicence;
    ref DZLLicenceCraftedItem craftedItem;
    ref DZLLicenceCraftItemCollection craftItems;
    ref DZLLicenceToolItemCollection toolItems;
    int durationForCrafting;
    bool showNotOnMapInAlmanac = false;

}
