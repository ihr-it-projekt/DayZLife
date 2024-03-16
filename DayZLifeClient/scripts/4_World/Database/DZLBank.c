class DZLBank: DZLFileSerializer {
    private string version = "2";
    int moneyAtBank = 0;
    ref DZLDate lastRaidTime;
    private int lastRaidMoney = 0;
    private int taxSum = 0;
    private bool raidRuns = false;
    private string raidPosition = "0 0 0";
    private int countDownRaid;

    int GetCountDownRaid() {
        return countDownRaid;
    }

    bool RaidRuns() {
        return raidRuns;
    }

    vector GetRaidPosition() {
        return raidPosition.ToVector();
    }

    bool HasMoneyToRaid() {
        return "0 0 0" != raidPosition;
    }

    int GetTaxSum() {
        return taxSum;
    }

    bool CanPaybackRobtMoney(DZLPlayer player) {
        return player.HasEnoughMoney(lastRaidMoney);
    }

    int GetLastRaidMoney() {
        return lastRaidMoney;
    }

    void StartRaid(vector position, int _countDownRaid) {};
    void StopRaid() {};
    int PlayerRaidBank(DZLPlayer player, int percentage) {};
    bool CanUseBank(int raidCoolDownTimeInSeconds) {};
    int PaybackRobtMoney(DZLPlayer player) {};
}
