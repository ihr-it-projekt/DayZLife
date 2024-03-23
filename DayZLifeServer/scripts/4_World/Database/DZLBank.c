modded class DZLBank {

    void DZLBank() {
        if(LoadJSON()) {
            Init(DAY_Z_LIFE_SERVER_FOLDER_DATA, "bank");
            Save();
        }

        Init(DAY_Z_LIFE_SERVER_FOLDER_DATA, "bank");
        Load();

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

    void AddTax(int _taxSum) {
        taxSum += _taxSum;
        Save();
    }

    void AddMoney(int moneyToAdd) {
        moneyAtBank += moneyToAdd;
        Save();
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

    bool CanUseBank(int raidCoolDownTimeInSeconds) {
        DZLDate currentDate = new DZLDate();

        if(lastRaidTime && (currentDate.inSeconds - lastRaidTime.inSeconds < raidCoolDownTimeInSeconds)) return false;

        if(lastRaidTime) {
            lastRaidTime = null;
            Save();
        }

        return true;
    }

    override protected bool Read(FileSerializer ctx) {
        if(!ctx.Read(version)) return false;
        if(!ctx.Read(moneyAtBank)) return false;
        if(!ctx.Read(taxSum)) return false;
        if(!ctx.Read(lastRaidTime)) return false;
        if(!ctx.Read(raidRuns)) return false;
        if(!ctx.Read(raidPosition)) return false;
        if(!ctx.Read(countDownRaid)) return false;
        return true;
    }

    override protected void Write(FileSerializer ctx) {
        ctx.Write(version);
        ctx.Write(moneyAtBank);
        ctx.Write(taxSum);
        ctx.Write(lastRaidTime);
        ctx.Write(raidRuns);
        ctx.Write(raidPosition);
        ctx.Write(countDownRaid);
    }

    private bool LoadJSON() {
        if(FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA + "bank.json")) {
            JsonFileLoader<DZLBank>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA + "bank.json", this);
            DeleteFile(DAY_Z_LIFE_SERVER_FOLDER_DATA + "bank.json");
            return true;
        }
        return false;
    }

}
