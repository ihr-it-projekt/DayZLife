class DZLCarStorage: DZLSaveModel
{
	string fileName = "";
    ref array<ref DZLCarStoreItem> items;

    void DZLCarStorage(string playerId) {
        fileName = "car_" + playerId + ".json";
        if (!Load()) {
            items = new array<ref DZLCarStoreItem>;
            mustSave = true;
        }
    }

    void Add(CarScript entity, vector storagePosition){
		items.Insert(new DZLCarStoreItem(entity, storagePosition));
		mustSave = true;
	}

	DZLCarStoreItem GetById(string id) {
	    foreach(DZLCarStoreItem item: items) {
	        if (item.id == id) {
	            return item;
	        }
	    }

	    return null;
	}
	
	void RemoveItem(DZLCarStoreItem item) {
		items.RemoveItem(item);
		mustSave = true;
	}

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_CAR + fileName)) {
            JsonFileLoader<DZLCarStorage>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_CAR + fileName, this);
            return true;
        }
        return false;
    }

    override protected bool DoSave(){
        if (GetGame().IsServer()) {
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_CAR);
            DZLJsonFileHandler<DZLCarStorage>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_CAR + fileName, this);
            return true;
        }
        return false;
    }
}
