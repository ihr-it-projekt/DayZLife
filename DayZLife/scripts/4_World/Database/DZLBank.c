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
	
	float PlayerRaidBank(DZLPlayer player, int percentage) {
		float moneyToRaid = percentage/100 * moneyAtBank;
		player.AddMoneyToPlayer(moneyToRaid);

		moneyAtBank -= moneyToRaid;
		Save();

		DZLPlayerIdentities identities = new DZLPlayerIdentities;
		ref array<string> playerIdentities = identities.playerIdentities;

		DZLPlayer playerRobt;
		foreach(string ident: playerIdentities) {
		    playerRobt = new DZLPlayer(ident);
		    if (!playerRobt.bank) continue;
		    playerRobt.AddMoneyToPlayerBank((percentage/100 * playerRobt.bank) * -1);
		}
		
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

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA);
            JsonFileLoader<DZLBank>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA + fileName, this);
        }
    }
}