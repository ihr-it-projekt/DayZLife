class DZLBank {
    private string version = "2";
    int moneyAtBank = 0;
    ref DZLDate lastRaidTime;
    string fileName = "bank.json";
    private int lastRaidMoney = 0;
    private int taxSum = 0;
    private bool raidRuns = false;
    private string raidPosition = "0 0 0";
    private int countDownRaid;

    void DZLBank() {
        Load();

        if(!version) {
            lastRaidMoney = 0;
            version = "1";
            taxSum = 0;
        }

        if(version == "1") {
            version = "2";
            raidPosition = "0 0 0";
            raidRuns = false;
            Save();
        }

        DZLBankRaidTimer.Get(this);
    }

    void CheckRaid() {
        countDownRaid--;
        if(countDownRaid <= 0) {
            lastRaidTime = new DZLDate();
            raidRuns = false;
            DZLBankRaidTimer.Get(this).Stop();
            DZLSendMessage(null, "#safe_is_open");
        }
        Save();
    }

    void StartRaid(vector position, int _countDownRaid) {
        if(!raidRuns) {
            raidRuns = true;
            raidPosition = position.ToString(false);
            Save();
            DZLBankRaidTimer.Get(this).Start();
            this.countDownRaid = _countDownRaid;
        }
    }

    void StopRaid() {
        DZLSendMessage(null, "#bank_rob_was_canceled");
        raidRuns = false;
        raidPosition = "0 0 0";
        DZLBankRaidTimer.Get(this).Stop();
        Save();
    }

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

    void AddTax(int _taxSum) {
        if(GetGame().IsServer()) {
            taxSum += _taxSum;
            Save();
        }
    }

    int GetTaxSum() {
        return taxSum;
    }

    void AddMoney(int moneyToAdd) {
        if(GetGame().IsServer()) {
            moneyAtBank += moneyToAdd;
            Save();
        }
    }

    int PlayerRaidBank(DZLPlayer player, int percentage) {
        lastRaidMoney = Math.Round(taxSum * percentage / 100);
        player.AddMoneyToPlayer(lastRaidMoney);
        taxSum -= lastRaidMoney;
        raidPosition = "0 0 0";
        Save();

        return lastRaidMoney;
    }

    int PaybackRobtMoney(DZLPlayer player) {
        player.AddMoneyToPlayer(lastRaidMoney * -1);
        taxSum += lastRaidMoney;
        int moneyBack = lastRaidMoney;

        lastRaidMoney = 0;
        Save();

        return moneyBack;
    }

    bool CanPaybackRobtMoney(DZLPlayer player) {
        return player.HasEnoughMoney(lastRaidMoney);
    }

    int GetLastRaidMoney() {
        return lastRaidMoney;
    }

    bool CanUseBank(int raidCoolDownTimeInSeconds) {
        DZLDate currentDate = new DZLDate();

        if(lastRaidTime && (currentDate.inSeconds - lastRaidTime.inSeconds < raidCoolDownTimeInSeconds)) return false;

        if(lastRaidTime) {
            lastRaidTime = null;
            Save();
        }

        return true;
    }

    private bool Load() {
        if(GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA + fileName)) {
            JsonFileLoader<DZLBank>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA + fileName, this);
            return true;
        }
        return false;
    }

    private bool Save() {
        if(GetGame().IsServer()) {
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA);
            DZLJsonFileHandler<DZLBank>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA + fileName, this);
            return true;
        }
        return false;
    }
}
