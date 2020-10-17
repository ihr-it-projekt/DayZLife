class DZLHouse {

    string fileName;
    string owner = "";
    string name = "";
	vector position;
	vector orientation;
	ref array<ref DZLStorageTypeBought> storage;
	

    void DZLHouse(Building building) {
        this.fileName = DZLHouse.GetFileName(building);
		if (!Load()) {
	        this.name = building.GetType();
			this.position = building.GetPosition();
			this.orientation = building.GetOrientation();
			this.storage = new array<ref DZLStorageTypeBought>;
			Save();
		}
    }
	
	static string GetFileName(Building building) {
		return building.GetPosition().ToString(false) + ".json";
	}

    void AddOwner(PlayerBase player) {
        owner = player.GetIdentity().GetId();
        Save();
    }
	
	void RemoveOwner() {
		owner = "";
		Save();
	}
	
	void AddStorage(DZLStorageTypeBought storageItem) {
		storage.Insert(storageItem);
		Save();
	}
	
	void RemoveStorage(DZLStorageTypeBought storageItem) {
		storage.RemoveItem(storageItem);
		Save();
	}
	
	int GetCountStorage() {
		return storage.Count();
	}
	
	bool HasStorage() {
		return GetCountStorage() != 0;
	}

	array<ref DZLStorageTypeBought> GetStorage() {
	    return storage;
	}

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE + fileName)) {
			JsonFileLoader<DZLHouse>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE + fileName, this);
			return true;
        }
		return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
			CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE);
			JsonFileLoader<DZLHouse>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE + fileName, this);
		}
    }
}