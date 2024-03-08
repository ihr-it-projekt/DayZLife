class DZLTraderHelper {
    static bool IsStackable(EntityAI item) {
        if(item && item.ConfigGetBool("canBeSplit")) {
            return true;
        }

        return false;
    }

    static float GetQuantityPrice(float price, EntityAI item = null) {
        if(DZLTraderHelper.IsStackable(item)) {
            price = price * GetQuantity(item);
        } else if(item) {
            price = price / GetQuantityMax(item) * GetQuantity(item);
        }

        return price;
    }

    static float GetQuantity(EntityAI item) {
        if(!item) return 1;

        int quantity = item.GetQuantity();
        if(quantity == 0) return 1;

        return quantity;
    }

    static float GetQuantityMax(EntityAI item) {
        if(!item) return 1;

        int quantity = item.GetQuantityMax();
        if(quantity == 0) return 1;

        return quantity;
    }

}