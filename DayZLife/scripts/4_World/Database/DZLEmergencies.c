class DZLEmergencies: DZLSaveModel
{
    ref array<string> emergencies;
	string fileName = "emergencies.json";

    void DZLEmergencies() {
        emergencies = new array<string>;
        mustSave = true;
    }

    void Add(string playerId) {
        emergencies.Insert(playerId);
        mustSave = true;
    }

    void Remove(string playerId) {
        emergencies.RemoveItem(playerId);
    }
	
    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA + fileName)) {
            JsonFileLoader<DZLEmergencies>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA + fileName, this);
            return true;
        }
        return false;
    }

    override protected bool DoSave(){
        if (GetGame().IsServer()) {
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA);
            DZLJsonFileHandler<DZLEmergencies>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA + fileName, this);
			return true;
        }
		return false;
    }
}
