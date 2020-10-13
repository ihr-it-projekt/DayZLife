class DZLPlayerHouse {
    private string fileName;
    ref array<string> playerHouseCollection;

    void DZLPlayerHouse(PlayerBase player) {
        fileName = player.GetIdentity().GetId();
        if (!Load()) {
            playerHouseCollection = new array<string>;
            Save();
        }
    }

    void AddHouse(ref DZLHouse house) {
        playerHouseCollection.Insert(house.fileName);
        Save();
	}
	
	void RemoveHouse(DZLHouse house) {
		foreach(int index, string fileName: playerHouseCollection) {
            if (house.fileName == fileName) {
				playerHouseCollection.Remove(index);
				Save();
				break;
			}
        }
	}

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName + ".json")) {
            JsonFileLoader<DZLPlayerHouse>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName + ".json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER);
            JsonFileLoader<DZLPlayerHouse>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName + ".json", this);
        }
    }
}