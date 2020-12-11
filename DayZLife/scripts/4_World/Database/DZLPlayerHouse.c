class DZLPlayerHouse {
    private string fileName;
    ref array<string> playerHouseCollection;
    ref array<string> playerHouseKeyCollection;

    void DZLPlayerHouse(string playerId) {
        fileName = playerId + "house.json";
        if (!Load()) {
            playerHouseCollection = new array<string>;
            playerHouseKeyCollection = new array<string>;
            Save();
        }
    }

    void AddHouse(notnull ref DZLHouse house) {

        playerHouseCollection.Insert(house.fileName);
        Save();
	}
	
	void RemoveHouse(notnull DZLHouse house) {
		int index = playerHouseCollection.Find(house.fileName);
		if (-1 != index) {
			playerHouseCollection.Remove(index);
			Save();
		}
	}
	
	bool HasHouse(notnull Building building) {
		string houseFileName = DZLHouse.GetFileName(building);
		return -1 != playerHouseCollection.Find(houseFileName);
	}
	
	bool HasKey(notnull Building building) {
		string houseFileName = DZLHouse.GetFileName(building);
		return -1 != playerHouseKeyCollection.Find(houseFileName);
	}
	
	void AddKey(notnull ref DZLHouse house) {
        playerHouseKeyCollection.Insert(house.fileName);
        Save();
	}
	
	void RemoveKey(notnull ref DZLHouse house) {
		int index = playerHouseKeyCollection.Find(house.fileName);
		if (-1 != index) {
			playerHouseKeyCollection.Remove(index);
			Save();
		}
	}
	
    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName)) {
            JsonFileLoader<DZLPlayerHouse>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER);
            DZLJsonFileHandler<DZLPlayerHouse>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, this);
        }
    }
}
