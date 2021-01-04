class DZLStoreItem: DZLIdModel
{
	float health
	string type;
	float quantity;
	ref array<ref DZLStoreItem> attached;
	bool isCar = false;
	vector positionOfStore;
	
	void DZLStoreItem() {
		attached = new array<ref DZLStoreItem>;
	}

	void Init(EntityAI item, vector positionOfStore, bool isAttached = false) {
	    SetItem(item, isAttached);
	    this.positionOfStore = positionOfStore;
        SetId();
	}

	private void SetItem(EntityAI item, bool isAttached = false) {
		health = item.GetHealth();
		SetType(item.GetType());
		
		ItemBase itemCast;
        ItemBase.CastTo(itemCast, item);
		
		if (itemCast) {
			quantity = itemCast.GetQuantity();
		}
		
		if(item.IsMagazine()) {
			Magazine mag = Magazine.Cast(item);
			
			if (!mag)
				return;
			quantity = mag.GetAmmoCount();
		} else if(item.IsAmmoPile()) {
			Ammunition_Base ammo = Ammunition_Base.Cast(item);
			
			if (!ammo) {
				return;
			}
			
			quantity = ammo.GetAmmoCount();
		}

		if (!isAttached) {
			array<EntityAI> itemsArray = new array<EntityAI>;
	        item.GetInventory().EnumerateInventory(InventoryTraversalType.INORDER, itemsArray);

			foreach(EntityAI itemAttached: itemsArray) {
				if (itemAttached != item) {
					DZLStoreItem storeItem = new DZLStoreItem();
					storeItem.Init(itemAttached, positionOfStore, true);
					attached.Insert(storeItem);
				}
			}
		}
	}
		
	float GetHealth() {
		return health;
	}
	
	float GetQuantity() {
		return quantity;
	}
	
	void SetType(string type) {
		this.type = type;
	}
	
	string GetType() {
		return type;
	}

	array<ref DZLStoreItem> GetAttached() {
		return attached;
	}
}
