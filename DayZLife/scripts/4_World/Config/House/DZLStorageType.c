class DZLStorageType : DZLHouseExtension
{
    void DZLStorageType(string type, string description, int price) {
        this.type = type;
        this.description = description;
        this.price = price;
        isStorage = true;
    }
}
