class DZLLicenceToolItem: DZLLicenceCraftItem
{
    int damageToTool;

    void DZLLicenceToolItem(string type, int quantity, int health, int damageToTool){
        DZLLicenceCraftItem(type, quantity, health);
        this.damageToTool = damageToTool;
    }
}