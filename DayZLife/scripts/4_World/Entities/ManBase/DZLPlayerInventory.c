class DZLPlayerInventory
{
	private map<string, int> currencyValues;
	
	void SetConfig(map<string, int> currencyValues) {
		this.currencyValues = currencyValues;
	}
	
    bool PlayerHasEnoughMoney(DayZPlayer player, int money) {
        int amount = GetPlayerMoneyAmount(player);

        DebugMessageDZL("Has money: " + amount.ToString());
        DebugMessageDZL("must have money: " + money.ToString());

        return money <= amount;
    }

    int GetPlayerMoneyAmount(DayZPlayer player)
    {
        if (!player) {
            return 0;
        }

        int currencyAmount = 0;

        array<EntityAI> itemsArray = new array<EntityAI>;
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);

        ItemBase item;
        for (int i = 0; i < itemsArray.Count(); i++)
        {
            Class.CastTo(item, itemsArray.Get(i));
			
            if(item && item.GetType()) {
                 DebugMessageDZL("Inventory item type: " + item.GetType());
				int value = currencyValues.Get(item.GetType());
				if (value) {
					currencyAmount += value * item.GetQuantity();
				}
			}
        }

        return currencyAmount;
    }

    int AddMoneyToPlayer(DayZPlayer player, float moneyCount) {
        array<EntityAI> itemsArray = new array<EntityAI>;
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);

        ItemBase item;
		int currencyAmount = 0;
        for (int i = 0; i < itemsArray.Count(); i++)
        {
            Class.CastTo(item, itemsArray.Get(i));
			
            if(item && item.GetType()) {
				int value = currencyValues.Get(item.GetType());
				if (value) {
					currencyAmount += value * item.GetQuantity();
					GetGame().ObjectDelete(item);
				}
			}
        }
		
		currencyAmount = currencyAmount + moneyCount;

        if (currencyAmount > 0) {
            currencyAmount = AddNewMoneyItemToInventory(player, currencyAmount);
        }

        return currencyAmount;
    }

    private int AddNewMoneyItemToInventory(DayZPlayer player, float moneyCount) {
        InventoryLocation inventoryLocation = new InventoryLocation;
		
		int selectedValue = 0;
        string selectedType = "";
        foreach(string type, int value: currencyValues) {
            if (moneyCount >= value && selectedValue < value) {
                selectedValue = value;
                selectedType = type;
            }
        }

		if (selectedValue == 0) {
		    return 0;
		}
		
		EntityAI chipsEntity;
        if (player.GetInventory().FindFirstFreeLocationForNewEntity(selectedType, FindInventoryLocationType.ANY, inventoryLocation)) {
            chipsEntity = player.GetHumanInventory().CreateInInventory(selectedType);
		}
		
		if (!chipsEntity && !player.GetHumanInventory().GetEntityInHands()) {
            chipsEntity = player.GetHumanInventory().CreateInHands(selectedType);
		} 
		
		if (!chipsEntity) {
            chipsEntity = player.SpawnEntityOnGroundPos(selectedType, player.GetPosition());
		}
		
		if (!chipsEntity) {
			return 0;
		}
		
        moneyCount = AddMoney(selectedValue, moneyCount, chipsEntity);

        if(moneyCount) {
            moneyCount = AddNewMoneyItemToInventory(player, moneyCount);
        }

        return moneyCount;
    }

    private int AddMoney(int factor, float moneyToAdd, EntityAI entity) {
        ItemBase item;
        ItemBase.CastTo(item, entity);

        int maxAmount = item.GetQuantityMax();
		
		int countAddFromType = Math.Floor(moneyToAdd / factor);

        if (countAddFromType > maxAmount) {
            moneyToAdd -= maxAmount * factor;
            item.SetQuantity(maxAmount);
        } else {
            item.SetQuantity(countAddFromType);
            moneyToAdd -= countAddFromType * factor;
        }
		
		if (moneyToAdd < 1) {
			moneyToAdd = 0;
		}
        
		return moneyToAdd;
    }
};