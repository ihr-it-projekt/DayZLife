class DZLInventoryExtension: DZLHouseExtension
{
	void DZLInventoryExtension(string id, string description, int price, int level) {
        this.id = id;
        this.description = description;
        this.price = price;
        this.level = level;
        isHouseInventory = true;
    }
}
