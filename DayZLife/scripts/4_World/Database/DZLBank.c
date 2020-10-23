class DZLBank
{
    float moneyAtBank = 0;
    bool raidRuns = false;
	ref DZLDate lastRaidTime;
	string fileName = "bank.json";
	
	private ref DZLBankingConfig config;

    void DZLBank() {
        if (!Load()) {
            Save();
        }
		
		config = new DZLBankingConfig();
    }

    void AddMoney(float moneyToAdd) {
        if (GetGame().IsServer() && CanUseBank()) {
            moneyAtBank += moneyToAdd;
            Save();
        }
    }
	
	float PlayerRaidBank(DZLPlayer player, int percentage) {
		float moneyToRaid = percentage/100 * moneyAtBank;
		
		player.money += moneyToRaid;
		
		moneyAtBank -= moneyToRaid;
		
		Save();

		DZLPlayerIdentities identities = new DZLPlayerIdentities;

		ref array<string> playerIdentities = identities.playerIdentities;

		DZLPlayer playerRobt;
		foreach(string ident: playerIdentities) {
		    playerRobt = new DZLPlayer(ident);

		    if (!playerRobt.bank) continue;

		    moneyToRaid = percentage/100 * playerRobt.bank;
		    playerRobt.AddMoneyToPlayerBank(moneyToRaid * -1);
		}
		
		return moneyToRaid;
	}
	
	bool CanUseBank() {
		if (raidRuns) return false;
		
		DZLDate currentDate = new DZLDate();
		
		if (lastRaidTime && (currentDate.inSeconds - lastRaidTime.inSeconds < config.raidCoolDownTimeInSeconds)) return false;
		
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