class DZLLicenceCraftItem {
    string type;
    int quantity;
    int health;
    [NonSerialized()] string lower;

    void DZLLicenceCraftItem(string _type, int _quantity, int _health) {
        type = _type;
        quantity = _quantity;
        health = _health;
    }

    string GetKey() {
        return GetLowerCaseType() + health.ToString();
    }

    string GetLowerCaseType() {
        if(lower) return lower;
        lower = type;
        lower.ToLower();

        return lower;
    }
}