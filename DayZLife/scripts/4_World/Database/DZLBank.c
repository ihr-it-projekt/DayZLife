class DZLBank
{
    int moneyAtBank = 0;
    bool raidRuns = false;
	ref DZLDate lastRaidTime;
	string fileName = "bank.json";
	
    void DZLBank() {
        if (!Load()) {
            Save();
        }
    }

    void AddMoney(int moneyToAdd) {
        if (GetGame().IsServer()) {
            moneyAtBank += moneyToAdd;
            Save();
        }
    }
	
	int PlayerRaidBank(DZLPlayer player, int percentage) {
		DZLPlayerIdentities identities = DZLDatabaseLayer.Get().GetPlayerIds();
		array<string> playerIdentities = identities.playerIdentities;

		int moneyToRaid = 0;
		foreach(string ident: playerIdentities) {
			DZLPlayer playerRobt = DZLDatabaseLayer.Get().GetPlayer(ident);
		    if (!playerRobt.HasBankMoney()) continue;
		    if (player.fileName == playerRobt.fileName) continue;

			float moneyToSteal = Math.Round(playerRobt.GetBankMoney() * percentage / 100);
			
		    playerRobt.AddMoneyToPlayerBank(moneyToSteal * -1);
		    moneyToRaid += moneyToSteal;
		}

        player.AddMoneyToPlayer(moneyToRaid);
        moneyAtBank -= moneyToRaid;
        Save();
		
		return moneyToRaid;
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
