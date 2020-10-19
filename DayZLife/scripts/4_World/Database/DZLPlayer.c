class DZLPlayer {
    private string fileName;
    int money = 0;
    int bank = 0;

    void DZLPlayer(notnull PlayerBase player) {
        fileName = player.GetIdentity().GetId() + ".json";
        if (!Load()) {
            if (DAY_Z_LIFE_DEBUG) {
                money = 100000;
            }

            Save();
        }
    }
	
	void AddMoneyToPlayer(float moneyCount) {
        if (!DayZGame().IsClient()) {
			money += moneyCount;
		    Save();
		}
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName)) {
            JsonFileLoader<DZLPlayer>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER);
            JsonFileLoader<DZLPlayer>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, this);
        }
    }
}