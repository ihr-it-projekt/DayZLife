class DLPlayerHouse {
    private string fileName;
    ref array<ref DLHouse> playerHouseCollection;


    void DLPlayerHouse(PlayerBase player) {
        fileName = player.GetIdentity().GetId();
        if (!Load()) {
            playerHouseCollection = new array<ref DLHouse>;
            Save();
        }
    }

    void AddHouse(ref DLHouse house) {
        playerHouseCollection.Insert(house);
	}
	
	void RemoveHouse(DLHouse house) {
		foreach(int index, DLHouse tempHouse: playerHouseCollection) {
            if (house.fileName == tempHouse.fileName) {
				playerHouseCollection.Remove(index);
				Save();
				break;
			}
        }
	}


    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName + ".json")) {
            JsonFileLoader<DLPlayerHouse>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName + ".json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER);
            JsonFileLoader<DLPlayerHouse>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName + ".json", this);
        }
    }
}