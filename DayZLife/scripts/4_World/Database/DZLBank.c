class DZLBank
{
    int moneyAtBank = 0;
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

    void AddTax(int _taxSum) {
        if (GetGame().IsServer()) {
            taxSum += _taxSum;
            Save();
        }
    }

    int GetTaxSum() {
        return taxSum;
    }

	void AddMoney(int moneyToAdd) {
        if (GetGame().IsServer()) {
            moneyAtBank += moneyToAdd;
            Save();
        }
    }

	int PlayerRaidBank(DZLPlayer player, int percentage) {
        lastRaidMoney =  Math.Round(taxSum * percentage / 100);
        player.AddMoneyToPlayer(lastRaidMoney);
        taxSum -= lastRaidMoney;
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
		
		if (lastRaidTime && (currentDate.inSeconds - lastRaidTime.inSeconds < raidCoolDownTimeInSeconds)) return false;
		
		if (lastRaidTime) {
			lastRaidTime = null;
			Save();
		}
		
		return true;
	}

    void RaidIsFinished() {
        lastRaidTime = new DZLDate();
		
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
