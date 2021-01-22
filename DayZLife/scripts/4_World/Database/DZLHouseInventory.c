class DZLHouseInventory
{
    private string version = "1";
    private string fileName = "";
    private int countOfStorage;
    private ref array<ref DZLStoreItem> store;

    void DZLHouseInventory(string playerId, vector position) {
        fileName = "house_inventory" + playerId + position.ToString(false) + ".json";

        if (!Load()) {
            store = new array<ref DZLStoreItem>;
            Save();
        }
    }

    void Delete() {
        DeleteFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName);
    }

    void IncreaseStorage(int add) {
        countOfStorage += add;
        Save();
    }

    bool CanAddToStore(array<EntityAI> items) {
        if (items.Count() <= GetLeftStorage()) {
            foreach(EntityAI item: items) {
                CargoBase cargo = item.GetInventory().GetCargo();
                if (cargo && cargo.GetItemCount() > 0) {
                    return false;
                }
            }
        } else {
            return false;
        }

        return true;
    }

    int GetMaxStore() {
        return countOfStorage;
    }

    int GetUsedStorage() {
        return store.Count();
    }
	
	int GetLeftStorage() {
		return countOfStorage - store.Count();
	}
	
	int GetLevel(int inventoryItemsPerLevel) {
		return countOfStorage / inventoryItemsPerLevel;
	}

    void AddToStore(array<EntityAI> items) {
        foreach(EntityAI item: items) {
			DZLStoreItem storeItem = new DZLStoreItem();
			storeItem.Init(item, "0 0 0", false);
            store.Insert(storeItem);
        }
        Save();
    }

    DZLStoreItem GetById(string id) {
        foreach(DZLStoreItem item: store) {
            if (item.id == id) {
                return item;
            }
        }

        return null;
    }

	void Remove(DZLStoreItem item) {
	    store.RemoveItem(item);
	    Save();
	}

	array<ref DZLStoreItem> GetStore() {
		return store;
	}

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName)) {
            JsonFileLoader<DZLHouseInventory>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, this);
            return true;
        }
        return false;
    }

    private bool Save(){
        if (GetGame().IsServer()) {
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER);
            DZLJsonFileHandler<DZLHouseInventory>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, this);
            return true;
        }
        return false;
    }
}
