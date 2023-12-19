
class DZLInventoryExtension: DZLHouseExtension {
    void DZLInventoryExtension(string id, string description, int price) {
        this.id = id;
        this.description = description;
        this.price = price;
        isHouseInventory = true;
    }
}
