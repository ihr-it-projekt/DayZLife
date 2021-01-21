class DZLPlayer
{
    string fileName = "";
    string dayZPlayerId = "";
    private int money = 0;
    private int bank = 0;
    private bool isCop = false;
    private bool isMedic = false;
    string playerName = "";
	int onlineTimeCivil = 0;
	int onlineTimeMedic = 0;
	int onlineTimeCop = 0;
	int arrestTimeInMinutes = 0;
	string arrestReason = "";
	private string activeJob = DAY_Z_LIFE_JOB_CIVIL;
	ref DZLDate lastLoginDate;
	ref TStringArray licenceIds;
	private string deadState = DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_NONE;
	ref array<ref DZLStoreItem> itemsStore;
	private string version = "2";

    void DZLPlayer(string playerId, int moneyToAdd = 0) {
        fileName = playerId + ".json";
        if (!Load()) {
            bank = moneyToAdd;
            this.dayZPlayerId = playerId;
			licenceIds = new TStringArray;

			DZLDatabaseLayer.Get().GetBank().AddMoney(bank);
		}

		DZLPlayerIdentities idents = DZLDatabaseLayer.Get().GetPlayerIds();
        idents.AddPlayer(playerId);
		
		if (!version) {
			arrestReason = "";
			version = "1";
		}

		if (version == "1") {
            deadState = DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_NONE;
            itemsStore = new array<ref DZLStoreItem>;
            version = "2";
        }
		Save();
    }

    bool IsPlayerInArrest() {
        return arrestTimeInMinutes != 0;
    }
	
	void ArrestCountDown() {
		--arrestTimeInMinutes;
		Save();
	}

    void ArrestPlayer(string reason, int time) {
        arrestTimeInMinutes = time;
		arrestReason = reason;
		Save();
    }

    void SetActiveJob(string job) {
        activeJob = job;
        Save();
    }

    string GetActiveJob() {
        if (activeJob == "") {
            activeJob = DAY_Z_LIFE_JOB_CIVIL;
            Save();
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
		Save();
	}
	
	void UpdateOnlineTime() {
		if (activeJob == DAY_Z_LIFE_JOB_COP) {
			onlineTimeCop++;
		} else if (activeJob == DAY_Z_LIFE_JOB_MEDIC) {
			onlineTimeMedic++;
		} else {
			onlineTimeCivil++;
		}
		
		Save();
	}
	
	void ResetOnlineTime() {
		if (activeJob == DAY_Z_LIFE_JOB_COP) {
			onlineTimeCop = 0;
		} else if (activeJob == DAY_Z_LIFE_JOB_MEDIC) {
			onlineTimeMedic = 0;
		} else {
			onlineTimeCivil = 0;
		}
		
		Save();
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
        Save();
    }
	
    void UpdateMedic(bool isMedic) {
        this.isMedic = isMedic;
        Save();
    }

    bool IsCop() {
        return isCop;
    }
	
    bool IsMedic() {
        return isMedic;
    }

    void UpdateName(string playerName) {
        this.playerName = playerName;
        lastLoginDate = new DZLDate();
        Save();
    }
	
	void AddMoneyToPlayer(int moneyCount) {
        if (DayZGame().IsServer()) {
            DZLLogMoneyTransaction(dayZPlayerId, "player", money, money + moneyCount, moneyCount);
			money += moneyCount;
		    Save();
		}
    }

	void AddMoneyToPlayerBank(int moneyCount) {
        if (DayZGame().IsServer()) {
            DZLLogMoneyTransaction(dayZPlayerId, "bank", bank, bank + moneyCount, moneyCount);
			bank += moneyCount;
		    Save();
		}
    }

    bool HasEnoughMoney(int amount) {
        return money >= amount;
    }

    bool HasMoney() {
        return money > 0;
    }

    bool HasBankMoney() {
        return bank > 0;
    }

    int GetBankMoney() {
        return bank;
    }

    int GetMoney() {
        return money;
    }

    int GetAllMoney() {
        return money + bank;
    }

    void PlayerHasDied() {
        money = 0;
        Save();
    }

    void SetDieState() {
        deadState = DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_IS_DEAD;
        Save();
    }

    void SetWillHealByMedic() {
        deadState = DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_NEW_SPAWN_MEDIC;
        Save();
    }

    void SetWillHealByHospital() {
        deadState = DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_NEW_SPAWN_HOSPITAL;
        Save();
    }

    void ResetDeadState() {
        deadState = DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_NONE;
        itemsStore = new array<ref DZLStoreItem>;;
        Save();
    }

    void SaveItems(PlayerBase player) {
        itemsStore = new array<ref DZLStoreItem>;
        DZLStoreItem items = new DZLStoreItem;
		items.Init(player, player.GetPosition(), false);

		itemsStore.Insert(items);
        Save();
    }

    DZLStoreItem GetPlayerData() {
        return itemsStore.Get(0);
    }

    bool WillDie() {
        return deadState == DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_IS_DEAD;
    }

    bool WillHealByMedic() {
        return deadState == DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_NEW_SPAWN_MEDIC;
    }

    bool WillHealByHospital() {
        return deadState == DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_NEW_SPAWN_HOSPITAL;
    }

    bool HasNoDieState() {
        return deadState == DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_NONE;
    }

    void TransferFromPlayerToOtherPlayer(DZLPlayer playerTarget) {
        DZLLogMoneyTransaction(dayZPlayerId, "player", money, 0, money);
        playerTarget.AddMoneyToPlayer(money);
        money = 0;
        Save();
    }
	
	void DepositMoneyFromPlayerToOtherPlayer(DZLPlayer playerTarget, int moneyToTransfer) {
		DZLLogMoneyTransaction(dayZPlayerId, "player", money, money - moneyToTransfer, moneyToTransfer * -1);
		playerTarget.AddMoneyToPlayer(moneyToTransfer);
		money -= moneyToTransfer;
		
		Save();
	}
	
	int DepositMoneyToOtherPlayer(DZLPlayer playerTarget, int moneyToTransfer) {
	    int moneyBankAdd = moneyToTransfer;

		playerTarget.AddMoneyToPlayerBank(moneyToTransfer);
		
		if (money > 0) {
			if (money < moneyToTransfer) {
			    DZLLogMoneyTransaction(dayZPlayerId, "player", money, money, 0);
				moneyToTransfer -= money;
				money = 0;
			} else {
			    DZLLogMoneyTransaction(dayZPlayerId, "player", money, money - moneyToTransfer, moneyToTransfer * -1);
				money -= moneyToTransfer;
				moneyToTransfer = 0;
			}
		}
		
		if (moneyToTransfer > 0) {
		    DZLLogMoneyTransaction(dayZPlayerId, "bank", bank, bank - moneyToTransfer, moneyToTransfer * -1);
			bank -= moneyToTransfer;
			moneyBankAdd -= moneyToTransfer;
		}
		
		Save();
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
		Save();
	}

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName)) {
            JsonFileLoader<DZLPlayer>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, this);
            return true;
        }
        return false;
    }

    private bool Save(){
        if (GetGame().IsServer()) {
            if (dayZPlayerId + ".json" != fileName) {
                LogMessageDZL("Can not save PlayerData. There are inconsistent in your player database: Please check file:" + fileName);
                return false;
            }
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER);
            DZLJsonFileHandler<DZLPlayer>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, this);
			return true;
        }
		return false;
    }
}
