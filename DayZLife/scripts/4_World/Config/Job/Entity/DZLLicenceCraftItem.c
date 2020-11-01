class DZLLicenceCraftItem
{
    string type;
    int quantity;
    int health;


    void DZLLicenceCraftItem(string type, int quantity, int health){
        this.type = type;
        this.quantity = quantity;
        this.health = health;
    }

    string GetLowerCaseType() {
        string lower = type;
        lower.ToLower();

        return lower;
    }
}