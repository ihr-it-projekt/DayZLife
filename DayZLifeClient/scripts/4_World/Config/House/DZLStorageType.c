class DZLStorageType : DZLHouseExtension {
    void DZLStorageType(string id, string type, string description, int price) {
        this.id = id;
        this.type = type;
        this.description = description;
        this.price = price;
        isStorage = true;
    }
}
