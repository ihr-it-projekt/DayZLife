class DZLFoundLicenseCraftItems {
    string type;
    string lowerType;
    int neededQuantity = 1;
    int neededHealth = 100;
    float foundQuantity = 0;
    ref array<EntityAI> items = new array<EntityAI>();

    void DZLFoundLicenseCraftItems(string _type, int _neededQuantity, int _neededHealth) {
        type = _type;
        lowerType = _type;
        lowerType.ToLower();
        neededQuantity = _neededQuantity;
        neededHealth = _neededHealth;
    }

    bool AddItem(EntityAI item) {
        if(CanUsed()) return false;
        string lowerTypeItem = item.GetType();
        lowerTypeItem.ToLower();
        if(lowerType != lowerTypeItem) return false;
        if(GetGame().IsServer() && item.GetHealth() < neededHealth) return false;

        foundQuantity += DZLTraderHelper.GetQuantity(item);
        items.Insert(item);

        return true;
    }

    bool CanUsed() {
        return foundQuantity >= neededQuantity;
    }

    void Use(PlayerIdentity identity) {
        foreach(EntityAI item: items) {
            float itemQuantity = DZLTraderHelper.GetQuantity(item);

            if(itemQuantity > neededQuantity) {
                ItemBase iBase = ItemBase.Cast(item);
                iBase.SetQuantity(itemQuantity - neededQuantity);
                DZLLogCrafting(identity.GetId(), "licence crafting reduce quantity resource", type);
                break;
            }

            neededQuantity -= itemQuantity;
            DZLLogCrafting(identity.GetId(), "licence crafting delete resource", type);
            GetGame().ObjectDelete(item);
        }
    }

    string GetErrorMessage() {
        string displayName = DZLDisplayHelper.GetItemDisplayName(type);
        return displayName + " #neededQuantity:" + neededQuantity + " #neededHealth: " + neededHealth + " #found " + foundQuantity + "\n";
    }
}