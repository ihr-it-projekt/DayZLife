class DZLMoneyConfig: DZLMoneyServerConfig {

    void DZLMoneyConfig() 
	{
        if(!Load()) {
            currencyValues = new map<string, int>;
            currencyValues.Set("Money_Euro1", 1);
            currencyValues.Set("Money_Euro2", 2);
            currencyValues.Set("Money_Euro5", 5);
            currencyValues.Set("Money_Euro10", 10);
            currencyValues.Set("Money_Euro20", 20);
            currencyValues.Set("Money_Euro50", 50);
            currencyValues.Set("Money_Euro100", 100);
            currencyValues.Set("Money_Euro200", 200);
            currencyValues.Set("Money_Euro500", 500);

            Save();
        }
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "money.json")) {
			JsonFileLoader<DZLMoneyConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "money.json", this);
			return true;
        }
		return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
			CheckDZLConfigPath();
			JsonFileLoader<DZLMoneyConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "money.json", this);
		}
    }

}