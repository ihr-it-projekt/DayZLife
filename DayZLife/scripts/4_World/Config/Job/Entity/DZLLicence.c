class DZLLicence
{
	int price;
	string name;
	vector position;
	int range;
	string dependencyLicence;
	string id;
    ref DZLLicenceCraftedItem craftedItem;
	ref DZLLicenceCraftItemCollection craftItems;
	ref DZLLicenceToolItemCollection toolItems;
	int durationForCrafting;


	void DZLLicence(int price, string name, vector position, int range, string dependencyLicence, ref DZLLicenceCraftedItem craftedItem, int durationForCrafting, DZLLicenceToolItemCollection toolItems, DZLLicenceCraftItemCollection craftItems) {
		this.price = price;
		this.name = name;
		this.position = position;
		this.range = range;
		this.dependencyLicence = dependencyLicence;
        this.craftedItem = craftedItem;
        this.durationForCrafting = durationForCrafting;
        this.toolItems = toolItems;
        this.craftItems = craftItems;
        
		SetId();
	}

	bool HasCorrectId() {
	    return id != "";
	}

	void SetId() {
	    id = Math.RandomInt(0, 100000000000).ToString();
	}
}