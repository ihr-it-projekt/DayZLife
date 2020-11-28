class DZLBankingConfig
{
    ref array<ref DZLBankingPosition> positionOfBankingPoints;
	bool showSumOfStoredCashInBank = true;
	int raidTimeBankInSeconds = 5;
	ref array<string> itemsCanUsedToRaidBank;
    int percentOfMoneyWhenRaid = 50;
	int raidCoolDownTimeInSeconds = 60;
	int maximumRaidDistanceToBank = 5;
	int startCapital = 50000;
	string version = "1";

    void DZLBankingConfig() {
        if(!Load()) {
            positionOfBankingPoints = new array<ref DZLBankingPosition>;
            itemsCanUsedToRaidBank = new array<string>;

            array<string> attachments = new array<string>;
            attachments.Insert("ManSuit_Black");
            attachments.Insert("SlacksPants_Black");
            attachments.Insert("ThickFramesGlasses");
            attachments.Insert("DressShoes_Black");

            if (DAY_Z_LIFE_DEBUG) {
                 // first Bank
                positionOfBankingPoints.Insert(new DZLBankingPosition("4660.000000 339.282990 10305.000000", "0 0 0", "SurvivorM_Boris", attachments));
                // second bank
                positionOfBankingPoints.Insert(new DZLBankingPosition("12326.892578 140.493500 12659.409180", "0 0 0", "SurvivorM_Rolf", attachments));

                itemsCanUsedToRaidBank.Insert("M4A1");
            } else {
                //TODO normal base config add
				positionOfBankingPoints.Insert(new DZLBankingPosition("6570.417969 6.000000 2449.841309", "-56 0 0", "SurvivorM_Rolf", attachments));

                itemsCanUsedToRaidBank.Insert("M4A1");
            }

            Save();
        }
		
		if (percentOfMoneyWhenRaid > 100) {
			percentOfMoneyWhenRaid = 100;
			
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