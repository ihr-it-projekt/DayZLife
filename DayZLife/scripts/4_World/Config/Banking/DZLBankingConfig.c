class DZLBankingConfig
{
	string version = "2";
    ref array<ref DZLBankingPosition> positionOfBankingPoints;
	bool showSumOfStoredCashInBank = true;
	int raidTimeBankInSeconds = 3600;
	ref array<string> itemsCanUsedToRaidBank;
    int percentOfMoneyWhenRaid = 15;
    int minimumOfMoneyWhatAPlayerMustHaveThatHeLoseMoneyAtBankRaid = 40000;
    int bonusPerCopWhenRobtMoneyWillPaidBackInPercent = 5;
    int sellTradingTax = 10;
	int raidCoolDownTimeInSeconds = 300;
	int maximumRaidDistanceToBank = 7;
	int startCapital = 5000;
	bool raidIsPlayerControlled = true;
	int minCountPlayerForRaid = 30;
	bool raidTimeControlled = true;
	int raidStartTimeHour = 14;
	int raidEndTimeHour = 22;
	int raidStartTimeMinute = 0;
	int raidEndTimeMinute = 59;

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

                itemsCanUsedToRaidBank.Insert("Deagle_Gold");
            } else {
				positionOfBankingPoints.Insert(new DZLBankingPosition("6570.417969 6.000000 2449.841309", "-56 0 0", "SurvivorM_Rolf", attachments));

                itemsCanUsedToRaidBank.Insert("Deagle_Gold");
            }

            Save();
        }
		
		if (percentOfMoneyWhenRaid > 100) {
			percentOfMoneyWhenRaid = 100;
			
			Save();
		}

		if (version == "1") {
            minimumOfMoneyWhatAPlayerMustHaveThatHeLoseMoneyAtBankRaid = 40000;
            bonusPerCopWhenRobtMoneyWillPaidBackInPercent = 5;
            sellTradingTax = 10;
            version = "2";
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
