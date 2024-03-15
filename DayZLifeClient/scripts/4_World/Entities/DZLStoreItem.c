class DZLStoreItem: DZLIdModel {
    float health
    string type;
    float quantity;
    ref array<ref DZLStoreItem> attached;
    bool isCar = false;
    vector positionOfStore;
    string parentId = "";


    void DZLStoreItem() {
        attached = new array<ref DZLStoreItem>;
    }

    void Init(EntityAI item, vector _positionOfStore, bool withCargo, bool ignoreHealth) {
        SetItem(item, withCargo, ignoreHealth);
        this.positionOfStore = _positionOfStore;
        SetId();
    }

    private void SetItem(EntityAI item, bool withCargo, bool ignoreHealth) {
        health = item.GetHealth();

        if(ignoreHealth) {
            health = item.GetMaxHealth();
        }

        SetType(item.GetType());

        ItemBase itemCast = ItemBase.Cast(item);

        if(itemCast) {
            quantity = itemCast.GetQuantity();
        }

        if(item.IsMagazine()) {
            Magazine mag = Magazine.Cast(item);

            if(!mag) return;
            quantity = mag.GetAmmoCount();
        } else if(item.IsAmmoPile()) {
            Ammunition_Base ammo = Ammunition_Base.Cast(item);

            if(!ammo) return;

            quantity = ammo.GetAmmoCount();
        }
        if(item.GetInventory()) {
            for(int i = 0; i < item.GetInventory().AttachmentCount(); i++) {
                EntityAI attachment = item.GetInventory().GetAttachmentFromIndex(i);
                if(attachment) {
                    DZLStoreItem storeItem = new DZLStoreItem();
                    storeItem.Init(attachment, positionOfStore, withCargo, ignoreHealth);
                    attached.Insert(storeItem);
                }
            }
        }


        CargoBase cargo = item.GetInventory().GetCargo();
        if(withCargo && cargo) {
            for(int z = 0; z < cargo.GetItemCount(); z++) {
                EntityAI inventoryItem = cargo.GetItem(z);
                if(inventoryItem) {
                    DZLStoreItem storeItemCargo = new DZLStoreItem();
                    storeItemCargo.Init(inventoryItem, positionOfStore, withCargo, ignoreHealth);
                    attached.Insert(storeItemCargo);
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

    void SetType(string _type) {
        this.type = _type;
    }

    string GetType() {
        return type;
    }

    array<ref DZLStoreItem> GetAttached() {
        return attached;
    }
}
