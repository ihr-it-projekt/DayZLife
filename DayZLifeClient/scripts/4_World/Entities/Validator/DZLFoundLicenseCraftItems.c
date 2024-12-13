class DZLFoundLicenseCraftItems {
    string type;
    string lowerType;
    int neededQuantity = 1;
    int reduceHealth = 0;
    int neededHealth = 100;
    float foundQuantity = 0;
    ref array<EntityAI> items = new array<EntityAI>();

    void DZLFoundLicenseCraftItems(string _type, int _neededQuantity, int _neededHealth, int _reduceHealth) {
        type = _type;
        lowerType = _type;
        lowerType.ToLower();
        neededQuantity = _neededQuantity;
        neededHealth = _neededHealth;
        reduceHealth = _reduceHealth;
    }

    bool AddItem(EntityAI item) {
        if(CanUsed()) return false;
        string lowerTypeItem = item.GetType();
        lowerTypeItem.ToLower();
        if(lowerType != lowerTypeItem) return false;
        if(g_Game.IsServer() && item.GetHealth() < neededHealth) return false;

        foundQuantity += DZLTraderHelper.GetQuantity(item);
        items.Insert(item);

        return true;
    }

    bool CanUsed() {
        return foundQuantity >= neededQuantity;
    }


    string GetErrorMessage() {
        string displayName = DZLDisplayHelper.GetItemDisplayName(type);
        return displayName + " #neededQuantity:" + neededQuantity + " #neededHealth: " + neededHealth + " #found " + foundQuantity + "\n";
    }
}