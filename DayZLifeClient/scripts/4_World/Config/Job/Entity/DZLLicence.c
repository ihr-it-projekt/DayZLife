class DZLLicence: DZLIdModel
{
	int price;
	string name;
	vector position;
	int range;
	string dependencyLicence;
    ref DZLLicenceCraftedItem craftedItem;
	ref DZLLicenceCraftItemCollection craftItems;
	ref DZLLicenceToolItemCollection toolItems;
	int durationForCrafting;


	void DZLLicence(int price, string name, vector position, string dependencyLicence, ref DZLLicenceCraftedItem craftedItem, int durationForCrafting, DZLLicenceToolItemCollection toolItems, DZLLicenceCraftItemCollection craftItems) {
		this.price = price;
		this.name = name;
		this.position = position;
		this.dependencyLicence = dependencyLicence;
        this.craftedItem = craftedItem;
        this.durationForCrafting = durationForCrafting;
        this.toolItems = toolItems;
        this.craftItems = craftItems;

		SetId();
	}
}
