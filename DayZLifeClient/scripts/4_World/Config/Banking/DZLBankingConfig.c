class DZLBankingConfig {
    string version = "5";
    ref array<ref DZLBankingPosition> positionOfBankingPoints;
    bool showSumOfStoredCashInBank = true;
    int raidTimeBankInSeconds = 3600;
    ref array<string> itemsCanUsedToRaidBank;
    int percentOfMoneyWhenRaid = 15;
    int bonusPerCopWhenRobtMoneyWillPaidBackInPercent = 5;
    int sellTradingTax = 10;
    int raidCoolDownTimeInSeconds = 300;
    int maximumRaidDistanceToBank = 7;
    int startCapital = 5000;
    bool useMoneyAsObject = false;
    ref map <string, int> currencyValues = new map<string, int>;
    bool raidIsCopControlled = true;
    int minCountCopsForRaid = 5;
    bool raidTimeControlled = true;
    int raidStartTimeHour = 14;
    int raidEndTimeHour = 22;
    int raidStartTimeMinute = 0;
    int raidEndTimeMinute = 59;
    bool canStartRaidIfShopRaidRuns = false;

}
