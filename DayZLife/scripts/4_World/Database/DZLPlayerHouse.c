class DZLPlayerHouse {
    private string fileName;
    ref array<string> playerHouseCollection;

    void DZLPlayerHouse(notnull PlayerIdentity player) {
        fileName = player.GetId() + "house.json";
        if (!Load()) {
            playerHouseCollection = new array<string>;
            Save();
        }
    }

    void AddHouse(notnull ref DZLHouse house) {

        playerHouseCollection.Insert(house.fileName);
        Save();
	}
	
	void RemoveHouse(notnull DZLHouse house) {
		foreach(int index, string fileName: playerHouseCollection) {
            if (house.fileName == fileName) {
				playerHouseCollection.Remove(index);
				Save();
				break;
			}
        }
	}
	
	bool HasHouse(notnull Building building) {
		string houseFileName = DZLHouse.GetFileName(building);
		foreach(string fileName: playerHouseCollection) {
            if (houseFileName == fileName) {
				return true;
			}
        }
		return false;
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
            JsonFileLoader<DZLPlayerHouse>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, this);
        }
    }
}