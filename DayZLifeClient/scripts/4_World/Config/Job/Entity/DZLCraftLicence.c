class DZLCraftLicence: DZLIdModel
{
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

	void DZLCraftLicence(int price, string name, vector position, string dependencyLicence, ref DZLLicenceCraftedItem craftedItem, int durationForCrafting, DZLLicenceToolItemCollection toolItems, DZLLicenceCraftItemCollection craftItems) {
		this.price = price;
		this.name = name;
		this.position = position;
		this.dependencyLicence = dependencyLicence;
        this.craftedItem = craftedItem;
        this.durationForCrafting = durationForCrafting;
        this.toolItems = toolItems;
        this.craftItems = craftItems;
        this.showNotOnMapInAlmanac = false;

		SetId();
	}
}
