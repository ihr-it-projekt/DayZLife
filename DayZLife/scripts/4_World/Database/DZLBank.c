class DZLBank
{
    float moneyAtBank = 0;
    string fileName = "bank.json";

    void DZLBank() {
        if (!Load()) {
            Save();
        }
    }

    void AddMoney(float moneyToAdd) {
        if (GetGame().IsServer()) {
            moneyAtBank += moneyToAdd;
            Save();
        }
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA + fileName)) {
            JsonFileLoader<DZLBank>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA + fileName, this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA);
            JsonFileLoader<DZLBank>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA + fileName, this);
        }
    }
}