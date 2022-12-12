modded class PlayerBase
{
    private ref TBLOLoadOutMenu loadOutMenu;


    void UpdatePlayerAtDependencies() {
        if (loadOutMenu && loadOutMenu.IsVisible()) {
            loadOutMenu.UpdatePlayer(this);
        }
    }

    private void InitMenu(TBLOBaseMenu menu) {
        menu.SetPlayer(this);
    }

	TBLOLoadOutMenu GetLoadOutMenu() {
		loadOutMenu = new TBLOLoadOutMenu();
		InitMenu(loadOutMenu);
		return loadOutMenu;
	}

	bool CloseMenu() {
	    bool hasDoAction = false;

		if (loadOutMenu && loadOutMenu.IsVisible()) {
			loadOutMenu.OnHide();
			hasDoAction = true;
		}
		
		return hasDoAction;
	}

	override void RemoveAllItems() {
		array<EntityAI> itemsArray = new array<EntityAI>;
		ItemBase item;
		GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
		
		for (int i = 0; i < itemsArray.Count(); i++) {
			Class.CastTo(item, itemsArray.Get(i));
			if (item && !item.IsInherited(SurvivorBase)) {
				GetGame().ObjectDelete(item);
			}	
		}
	}

}
