class DZLLicenceCraftItem {
    string type;
    int quantity;
    int health;
    [NonSerialized()] string lower;

    void DZLLicenceCraftItem(string type, int quantity, int health) {
        this.type = type;
        this.quantity = quantity;
        this.health = health;
    }

    string GetLowerCaseType() {
        if(lower) return lower;
        lower = type;
        lower.ToLower();

        return lower;
    }
}