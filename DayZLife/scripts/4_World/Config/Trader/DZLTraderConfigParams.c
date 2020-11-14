class DZLTraderConfigParams
{
	string configVersion = "1";

    void DZLTraderConfigParams()
    {
  		if (!Load()){

			Save();
		}
    }
	
    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "traderParams.json")) {
            JsonFileLoader<DZLTraderConfigParams>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "traderParams.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLTraderConfigParams>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "traderParams.json", this);
        }
    }
	
}