class DZLLicence: DZLIdModel
{
    int m_CommandUID;
	int price;
	string name;
	vector position;
	int range;
	string dependencyLicence;
    ref DZLLicenceCraftedItem craftedItem;
	ref DZLLicenceCraftItemCollection craftItems;
	ref DZLLicenceToolItemCollection toolItems;
	int durationForCrafting;


	void DZLLicence(int m_CommandUID, int price, string name, vector position, int range, string dependencyLicence, ref DZLLicenceCraftedItem craftedItem, int durationForCrafting, DZLLicenceToolItemCollection toolItems, DZLLicenceCraftItemCollection craftItems) {
		this.m_CommandUID = m_CommandUID;
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


}
