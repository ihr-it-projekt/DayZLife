modded class DZLBankingConfig {

    void DZLBankingConfig() {
        if(!Load()) {
            positionOfBankingPoints = new array<ref DZLBankingPosition>;
            itemsCanUsedToRaidBank = new array<string>;

            positionOfBankingPoints.Insert(new DZLBankingPosition("6601.550781 8.200232 2427.736328", "131.999939 0 0"));

            itemsCanUsedToRaidBank.Insert("Deagle_Gold");


            Save();
        }

        if(percentOfMoneyWhenRaid > 100) {
            percentOfMoneyWhenRaid = 100;

            Save();
        }

        if(version == "1") {
            bonusPerCopWhenRobtMoneyWillPaidBackInPercent = 5;
            sellTradingTax = 10;
            version = "2";
            Save();
        }

        if(version == "2") {
            version = "3";
            Save();
        }

        if(version == "3") {
            version = "4";
            Save();
        }

        if(version == "4") {
            version = "5";
            canStartRaidIfShopRaidRuns = false;
            minCountCopsForRaid = 5;
            raidIsCopControlled = true;
            Save();
        }

        if(version == "5") {
            version = "6";
            currencyValues = new map<string, int>;
            currencyValues.Set("MoneyRuble1", 1);
            currencyValues.Set("MoneyRuble5", 5);
            currencyValues.Set("MoneyRuble10", 10);
            currencyValues.Set("MoneyRuble25", 25);
            currencyValues.Set("MoneyRuble50", 50);
            currencyValues.Set("MoneyRuble100", 100);
            Save();
        }
    }

    private bool Load() {
        if(FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "banking.json")) {
            JsonFileLoader<DZLBankingConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "banking.json", this);
            return true;
        }
        return false;
    }

    private void Save() {
            CheckDZLConfigPath();
            JsonFileLoader<DZLBankingConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "banking.json", this);
    }
}
