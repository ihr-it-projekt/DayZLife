class DZLPlayer {
    string fileName;
    int money = 0;
    int bank = 0;
	
	ref TStringArray licenceIds;

    void DZLPlayer(string playerId, int moneyToAdd = 0) {
        fileName = playerId + ".json";
        if (!Load()) {
            money = moneyToAdd;
            if (DAY_Z_LIFE_DEBUG) {
                money = 100000;
            }

            DZLPlayerIdentities idents = new DZLPlayerIdentities;
            idents.AddPlayer(playerId);
			licenceIds = new TStringArray;
			
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

    bool HasEnoughMoney(int amount) {
        return money >= amount;
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
	
	string CanBuyLicence(notnull DZLLicence licenceToBuy, DZLLicence depLicence){
		if(money < licenceToBuy.price) return "#not_enough_money";
		if(HasLicense(licenceToBuy)) return "#your_already_have_the_licence";

		if(depLicence && HasDependencyLicense(depLicence)) return "";

		return "#you_have_not_the_dependency_licence";
	}

	bool HasDependencyLicense(notnull DZLLicence depLicence) {
	    return HasLicense(depLicence);
	}
	
	bool HasLicense(DZLLicence licenceToBuy) {
		foreach(string licenceId: licenceIds){
            if(licenceId == licenceToBuy.id){
                return true;
            }
        }
        return false;
	}
	
	void BuyLicence(DZLLicence licenceToBuy){
		money -= licenceToBuy.price;
		licenceIds.Insert(licenceToBuy.id);
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