class DZLPlayer {
    string fileName;
    int money = 0;
    int bank = 0;

    void DZLPlayer(string playerId) {
        fileName = playerId + ".json";
        if (!Load()) {
            if (DAY_Z_LIFE_DEBUG) {
                money = 100000;
            }

            DZLPlayerIdentities idents = new DZLPlayerIdentities;
            idents.AddPlayer(playerId);

            Save();
        }
    }
	
	void AddMoneyToPlayer(int moneyCount) {
        if (!DayZGame().IsClient()) {
			money += moneyCount;
		    Save();
		}
    }
	void AddMoneyToPlayerBank(int moneyCount) {
        if (!DayZGame().IsClient()) {
			bank += moneyCount;
		    Save();
		}
    }

    void PlayerHasDied() {
        money = 0;
        Save();
    }

    void TransferFromPlayerToOtherPlayer(DZLPlayer playerTarget) {
        playerTarget.AddMoneyToPlayer(money);
        money = 0;
        Save();
    }
	
	void DepositMoneyToOtherPlayer(DZLPlayer playerTarget, int moneyToTransfer) {
		playerTarget.AddMoneyToPlayerBank(moneyToTransfer);
		
		if (money > 0) {
			if (money < moneyToTransfer) {
				moneyToTransfer -= money;
				money = 0;
			} else {
				money -= moneyToTransfer;
				moneyToTransfer = 0;
			}
		}
		
		if (moneyToTransfer > 0) {
			bank -= moneyToTransfer;
		}
		
		Save();
	}

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName)) {
            JsonFileLoader<DZLPlayer>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER);
            JsonFileLoader<DZLPlayer>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, this);
        }
    }
}