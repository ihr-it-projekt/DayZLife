class DZLPlayerMoney {
    static ref DZLPlayerMoney instance;

    static DZLPlayerMoney Get(PlayerBase player) {
        if(!instance) {
            instance = new DZLPlayerMoney();
        }

        instance.player = player;

        return instance;
    }

    private PlayerBase player;
    private bool useMoneyFromLBMasterATM = false;

    bool HasEnoughMoney(int sum) {
        int amount = GetMoneyAmount();

        return sum <= amount;
    }

    int GetMoneyAmount() {
        if(!player) {
            return 0;
        }

        DZLBankingConfig config = DZLConfig.Get().bankConfig;
        if(!config.currencyValues) {
            return 0;
        }

        int currencyAmount = 0;

        array<EntityAI> itemsArray = new array<EntityAI>;
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);

        ItemBase item;
        for(int i = 0; i < itemsArray.Count(); i++) {
            Class.CastTo(item, itemsArray.Get(i));

            if(item && item.GetType()) {
                int value = config.currencyValues.Get(item.GetType());
                if(value) {
                    currencyAmount += value * item.GetQuantity();
                }
            }
        }

        return currencyAmount;
    }
};