class DZLPlayerHouse {
    private string fileName;
    ref array<ref DZLHouse> playerHouseCollection;


    void DZLPlayerHouse(PlayerBase player) {
        fileName = player.GetIdentity().GetId();
        if (!Load()) {
            playerHouseCollection = new array<ref DZLHouse>;
            Save();
        }
    }

    void AddHouse(ref DZLHouse house) {
        playerHouseCollection.Insert(house);
	}
	
	void RemoveHouse(DZLHouse house) {
		foreach(int index, DZLHouse tempHouse: playerHouseCollection) {
            if (house.fileName == tempHouse.fileName) {
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