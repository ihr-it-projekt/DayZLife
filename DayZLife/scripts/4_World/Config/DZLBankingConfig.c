class DZLBankingConfig
{
    ref array<ref DZLBankingPosition> positionOfBankingPoints;

    void DZLBankingConfig() {
        if(!Load()) {
            positionOfBankingPoints = new array<ref DZLBankingPosition>;
            array<string> attachments = new array<string>;
            attachments.Insert("ManSuit_Black");
            attachments.Insert("SlacksPants_Black");
            attachments.Insert("ThickFramesGlasses");
            attachments.Insert("DressShoes_Black");

            positionOfBankingPoints.Insert(new DZLBankingPosition("11053.101563 226.815567 12388.920898", "0 0 0", "SurvivorM_Boris", attachments));
            positionOfBankingPoints.Insert(new DZLBankingPosition("12326.892578 140.493500 12659.409180", "0 0 0", "SurvivorM_Rolf", attachments));
            Save();
        }
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "banking.json")) {
            JsonFileLoader<DZLBankingConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "banking.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLBankingConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "banking.json", this);
        }
    }
}