class DZLLicenceCraftItem {
    string type;
    int quantity;
    int health;
    int healthReduce = 0;
    [NonSerialized()] string lower;

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