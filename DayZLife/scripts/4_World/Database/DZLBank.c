class DZLBank
{
    int moneyAtBank = 0;
    bool raidRuns = false;
	ref DZLDate lastRaidTime;
	string fileName = "bank.json";
	private string version = "1";
	private int lastRaidMoney = 0;
	private int taxSum = 0;
	
    void DZLBank() {
        if (!Load()) {
            Save();
        }

        if (!version) {
            lastRaidMoney = 0;
            version = "1";
            taxSum = 0;
            Save();
        }
    }

    void AddTax(int taxSum) {
        if (GetGame().IsServer()) {
            taxSum += taxSum;
            Save();
        }
    }

    int GetTaxSum() {
        return tax;
    }

	void AddMoney(int moneyToAdd) {
        if (GetGame().IsServer()) {
            moneyAtBank += moneyToAdd;
            Save();
        }
    }

	int PlayerRaidBank(DZLPlayer player, int percentage, int minimumMoney) {
		DZLPlayerIdentities identities = DZLDatabaseLayer.Get().GetPlayerIds();
		array<string> playerIdentities = identities.playerIdentities;

		lastRaidMoney = 0;
		foreach(string ident: playerIdentities) {
			DZLPlayer playerRobt = DZLDatabaseLayer.Get().GetPlayer(ident);
		    if (!playerRobt.HasBankMoney() || player.fileName == playerRobt.fileName || playerRobt.GetAllMoney() < minimumMoney) {
		        playerRobt.ResetRobMoney();
		        continue;
		    }
		    lastRaidMoney += playerRobt.BankRobMoney(percentage);
		}

        player.AddMoneyToPlayer(lastRaidMoney);
        moneyAtBank -= lastRaidMoney;
        Save();
		
		return lastRaidMoney;
	}

	int PaybackRobtMoney(DZLPlayer player) {
	    DZLPlayerIdentities identities = DZLDatabaseLayer.Get().GetPlayerIds();
        array<string> playerIdentities = identities.playerIdentities;

        foreach(string ident: playerIdentities) {
            DZLDatabaseLayer.Get().GetPlayer(ident).GiveBackRobtMoney();
        }

        player.AddMoneyToPlayerBank(lastRaidMoney * -1);
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
		if (raidRuns) return false;
		
		DZLDate currentDate = new DZLDate();
		
		if (lastRaidTime && (currentDate.inSeconds - lastRaidTime.inSeconds < raidCoolDownTimeInSeconds)) return false;
		
		if (lastRaidTime) {
			lastRaidTime = null;
			Save();
		}
		
		return true;
	}

    void StartRaid() {
        raidRuns = true;
		Save();
    }

    void RaidIsFinished() {
        raidRuns = false;
        lastRaidTime = new DZLDate();
		
		Save();
    }
	
	void CancelRaid() {
		raidRuns = false;
		
		Save();
	}
	
    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA + fileName)) {
            JsonFileLoader<DZLBank>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA + fileName, this);
            return true;
        }
        return false;
    }

    private bool Save(){
        if (GetGame().IsServer()) {
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA);
            DZLJsonFileHandler<DZLBank>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA + fileName, this);
			return true;
        }
		return false;
    }
}
