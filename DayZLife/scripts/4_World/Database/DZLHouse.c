class DZLHouse {

    string fileName;
    string owner = "";
    string name = "";
	vector position;
	vector orientation;

    void DZLHouse(Building building) {
        this.fileName = building.GetPosition().ToString(false) + ".json";
        this.name = building.GetType();
		this.position = building.GetPosition();
		this.orientation = building.GetOrientation();

        Load();
        Save();
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
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE + fileName)) {
			JsonFileLoader<DZLHouse>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE + fileName, this);
        }
    }

    private void Save(){
        if (GetGame().IsServer()) {
			CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE);
			JsonFileLoader<DZLHouse>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE + fileName, this);
		}
    }
}