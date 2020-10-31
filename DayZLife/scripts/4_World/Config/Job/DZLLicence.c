class DZLLicence
{
	int price;
	string name;
	vector position;
	int range;
	string dependencyLicence;
	string id;
	string ItemThatCanBeCrafted;
    ref DZLLicenceCraftedItem craftedItem;
	ref array<ref DZLLicenceCraftItem> craftItems;
	ref array<ref DZLLicenceToolItem> toolItems;
	int durationForCrafting;


	void DZLLicence(int price, string name, vector position, int range, string dependencyLicence, ref DZLLicenceCraftedItem craftedItem, int durationForCrafting, array<ref DZLLicenceToolItem> toolItems, array<ref DZLLicenceCraftItem> craftItems) {
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
	    return id == name + dependencyLicence + price.ToString() + position.ToString(false) + range.ToString();
	}

	void SetId() {
	    id = name + dependencyLicence + price.ToString() + position.ToString(false) + range.ToString();
	}
}