modded class DZLPlayerMoney {

    int AddMoney(float moneyAmount) {
        if(moneyAmount == 0) return 0;

        array<EntityAI> itemsArray = new array<EntityAI>;
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
        DZLBankingConfig config = DZLConfig.Get().bankConfig;

        ItemBase item;
        int currencyAmount = 0;
        for(int i = 0; i < itemsArray.Count(); i++) {
            Class.CastTo(item, itemsArray.Get(i));

            if(item && item.GetType()) {
                int value = config.currencyValues.Get(item.GetType());
                if(value) {
                    currencyAmount += value * item.GetQuantity();
                    GetGame().ObjectDelete(item);
                }
            }
        }

        currencyAmount = currencyAmount + moneyAmount;

        if(currencyAmount > 0) {
            currencyAmount = AddNewMoneyItemToInventory(currencyAmount);
        }

        return currencyAmount;
    }

    private int AddNewMoneyItemToInventory(float moneyAmount) {
        InventoryLocation inventoryLocation = new InventoryLocation;

        int selectedValue = 0;
        string selectedType = "";
        DZLBankingConfig config = DZLConfig.Get().bankConfig;
        foreach(string type, int value: config.currencyValues) {
            if(moneyAmount >= value && selectedValue < value) {
                selectedValue = value;
                selectedType = type;
            }
        }

        if(selectedValue == 0) {
            return 0;
        }

        EntityAI moneyEntity;
        if(player.GetInventory().FindFirstFreeLocationForNewEntity(selectedType, FindInventoryLocationType.ANY, inventoryLocation)) {
            moneyEntity = player.GetHumanInventory().CreateInInventory(selectedType);
        }

        if(!moneyEntity && !player.GetHumanInventory().GetEntityInHands()) {
            moneyEntity = player.GetHumanInventory().CreateInHands(selectedType);
        }

        if(!moneyEntity) {
            moneyEntity = player.SpawnEntityOnGroundPos(selectedType, player.GetPosition());
        }

        if(!moneyEntity) {
            Print("Can not spawn: " + selectedType);
            return 0;
        }

        moneyAmount = AddMoneyItem(selectedValue, moneyAmount, moneyEntity);

        if(moneyAmount) {
            moneyAmount = AddNewMoneyItemToInventory(moneyAmount);
        }

        return moneyAmount;
    }

    private int AddMoneyItem(int factor, float moneyToAdd, EntityAI entity) {
        ItemBase item;
        ItemBase.CastTo(item, entity);

        int maxAmount = item.GetQuantityMax();

        int countAddFromType = Math.Floor(moneyToAdd / factor);

        if(countAddFromType > maxAmount) {
            moneyToAdd -= maxAmount * factor;
            item.SetQuantity(maxAmount);
        } else {
            item.SetQuantity(countAddFromType);
            moneyToAdd -= countAddFromType * factor;
        }

        if(moneyToAdd < 1) {
            moneyToAdd = 0;
        }

        return moneyToAdd;
    }
};