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

}
