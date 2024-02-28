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
        if(item.HasQuantity()) {
            return item.GetQuantity();
        }

        return 1.0;
    }

    static float GetQuantityMax(EntityAI item) {
        int quantity = 1;
        if(item) {
            quantity = item.GetQuantityMax();
        }

        if(quantity == 0) {
            quantity = 1;
        }

        return quantity;
    }

}