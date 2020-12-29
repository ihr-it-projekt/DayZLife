class DZLPlayer: DZLSaveModel
{
    string fileName = "";
    string dayZPlayerId = "";
    int money = 0;
    int bank = 0;
    bool isCop = false;
    string playerName = "";
	int onlineTimeCivil = 0;
	int onlineTimeMedic = 0;
	int onlineTimeCop = 0;
	int arrestTimeInMinutes = 0;
	private string activeJob = DAY_Z_LIFE_JOB_CIVIL;
	ref DZLDate lastLoginDate;
	ref TStringArray licenceIds;

    void DZLPlayer(string playerId, int moneyToAdd = 0) {
        fileName = playerId + ".json";
        if (!Load()) {
            bank = moneyToAdd;
//            if (DAY_Z_LIFE_DEBUG) {
//                money = 100000;
//            }
            this.dayZPlayerId = playerId;

            DZLPlayerIdentities idents = DZLDatabaseLayer.Get().GetPlayerIds();
            idents.AddPlayer(playerId);
			licenceIds = new TStringArray;

			DZLDatabaseLayer.Get().GetBank().AddMoney(bank);
			
            mustSave = true;
        }
    }

    bool IsPlayerInArrest() {
        return arrestTimeInMinutes != 0;
    }
	
	void ArrestCountDown() {
		--arrestTimeInMinutes;
		mustSave = true;	
	}

    void ArrestPlayer(int time) {
        arrestTimeInMinutes = time;
		mustSave = true;
    }

    void SetActiveJob(string job) {
        activeJob = job;
        mustSave = true;
    }

    string GetActiveJob() {
        if (activeJob == "") {
            activeJob = DAY_Z_LIFE_JOB_CIVIL;
            mustSave = true;
        }
        return activeJob;
    }
	
	bool IsActiveAsCop() {
		return DAY_Z_LIFE_JOB_COP == activeJob;
	}

	bool IsActiveAsMedic() {
		return DAY_Z_LIFE_JOB_MEDIC == activeJob;
	}

	bool IsActiveAsCivil() {
		return DAY_Z_LIFE_JOB_CIVIL == activeJob || activeJob == "";
	}
	
	void UpdateActiveJob(string job) {
		activeJob = job;
		mustSave = true;
	}
	
	void UpdateOnlineTime() {
		if (activeJob == DAY_Z_LIFE_JOB_COP) {
			onlineTimeCop++;
		} else if (activeJob == DAY_Z_LIFE_JOB_MEDIC) {
			onlineTimeMedic++;
		} else {
			onlineTimeCivil++;
		}
		
		mustSave = true;
	}
	
	void ResetOnlineTime() {
		if (activeJob == DAY_Z_LIFE_JOB_COP) {
			onlineTimeCop = 0;
		} else if (activeJob == DAY_Z_LIFE_JOB_MEDIC) {
			onlineTimeMedic = 0;
		} else {
			onlineTimeCivil = 0;
		}
		
		mustSave = true;
	}
	
	int GetActiveOnlineTime() {
		if (activeJob == DAY_Z_LIFE_JOB_COP) {
			return onlineTimeCop;
		} else if (activeJob == DAY_Z_LIFE_JOB_MEDIC) {
			return onlineTimeMedic;
		}
		return onlineTimeCivil;
	}

    void UpdateCop(bool isCop) {
        this.isCop = isCop;
        mustSave = true;
    }

    void UpdateName(string playerName) {
        this.playerName = playerName;
        lastLoginDate = new DZLDate();
        mustSave = true;
    }
	
	void AddMoneyToPlayer(int moneyCount) {
        if (!DayZGame().IsClient()) {
			money += moneyCount;
		    mustSave = true;
		}
    }
	void AddMoneyToPlayerBank(int moneyCount) {
        if (!DayZGame().IsClient()) {
			bank += moneyCount;
		    mustSave = true;
		}
    }

    bool HasEnoughMoney(int amount) {
        return money >= amount;
    }

    void PlayerHasDied() {
        money = 0;
        mustSave = true;
    }

    void TransferFromPlayerToOtherPlayer(DZLPlayer playerTarget) {
        playerTarget.AddMoneyToPlayer(money);
        money = 0;
        mustSave = true;
    }
	
	void DepositMoneyFromPlayerToOtherPlayer(DZLPlayer playerTarget, int moneyToTransfer) {
		playerTarget.AddMoneyToPlayer(moneyToTransfer);
		money -= moneyToTransfer;
		
		mustSave = true;
	}
	
	int DepositMoneyToOtherPlayer(DZLPlayer playerTarget, int moneyToTransfer) {
	    int moneyBankAdd = moneyToTransfer;

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
			moneyBankAdd -= moneyToTransfer;
		}
		
		mustSave = true;
		return moneyBankAdd;
	}
	
	string CanBuyLicence(notnull DZLLicence licenceToBuy, DZLLicence depLicence){
		if(money < licenceToBuy.price) return "#not_enough_money";
		if(HasLicense(licenceToBuy)) return "#your_already_have_the_licence";

		if (!depLicence) return "";

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
		mustSave = true;
	}

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName)) {
            JsonFileLoader<DZLPlayer>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, this);
            return true;
        }
        return false;
    }

    override protected bool DoSave(){
        if (GetGame().IsServer()) {
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER);
            DZLJsonFileHandler<DZLPlayer>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, this);
			return true;
        }
		return false;
    }
}
