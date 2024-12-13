modded class DZLFoundLicenseCraftItems {

    void UseItems(PlayerIdentity identity) {
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
            g_Game.ObjectDelete(item);
        }
    }

    void UseTool(PlayerIdentity identity) {
        foreach(EntityAI item: items) {
            item.DecreaseHealth("", "", reduceHealth);
            DZLLogCrafting(identity.GetId(), "licence crafting reduce health of tool", type);
        }
    }
}