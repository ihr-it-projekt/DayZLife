class DZLHouse {

    string fileName;
    string owner = "";
    string name = "";


    void DZLHouse(Building building) {
        this.fileName = building.GetPosition().ToString(false) + ".json";
        this.name = building.GetType();
        Load();
    }

    void AddOwner(PlayerBase player) {
        owner = player.GetIdentity().GetId();
        Save();
    }
	
	void RemoveOwner() {
		owner = "";
		Save();
	}

    private void Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE + fileName + ".json")) {
			JsonFileLoader<DZLHouse>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE + fileName + ".json", this);
        }
    }

    private void Save(){
        if (GetGame().IsServer()) {
			CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE);
			JsonFileLoader<DZLHouse>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE + fileName + ".json", this);
		}
    }
}