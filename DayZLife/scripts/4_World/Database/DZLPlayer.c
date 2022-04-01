class DZLPlayer
{
    string fileName = "";
    string dayZPlayerId = "";
    private int money = 0;
    private int bank = 0;
    private bool isCop = false;
    private string lastCopRank = "";
    private bool isMedic = false;
    private string lastMedicRank = "";
    private bool isArmy = false;
    private string lastArmyRank = "";
    private int robtMoney = 0;
    string playerName = "";
	int onlineTimeCivil = 0;
	int onlineTimeMedic = 0;
	int onlineTimeCop = 0;
	int arrestTimeInMinutes = 0;
	string arrestReason = "";
	private string activeJob = DAY_Z_LIFE_JOB_CIVIL;
	private string activeJobGrade = "Rekrut";
	ref DZLDate lastLoginDate;
	ref TStringArray licenceIds;
	private string deadState = DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_NONE;
	ref array<ref DZLStoreItem> itemsStore;
	private string version = "5";
	private ref array<ref DZLTicket> openTickets;
	private string fractionId = "";
	private ref array<string> fractionWherePlayerCanJoin;
	private ref DZLFraction fraction = null;

    void DZLPlayer(string playerId, int moneyToAdd = 0) {
        fileName = playerId + ".json";
        if (!Load()) {
            bank = moneyToAdd;
            this.dayZPlayerId = playerId;
			licenceIds = new TStringArray;

			DZLDatabaseLayer.Get().GetBank().AddMoney(bank);
			openTickets = new array<ref DZLTicket>;
		}

		DZLPlayerIdentities idents = DZLDatabaseLayer.Get().GetPlayerIds();
        idents.AddPlayer(playerId);

        if (version == "3") {
            activeJobGrade = "Rekrut";
        	openTickets = new array<ref DZLTicket>;
        }

        DZLPaycheck payCheck = DZLRankHelper.getCurrentPayCheck(this, DZLConfig.Get().jobConfig.paycheck);

        if (payCheck.rank != activeJobGrade) {
            activeJobGrade = payCheck.rank;
        }

        if (version != "5") {
            fractionId = "";
            fractionWherePlayerCanJoin = new array<string>;

            version = "5";
        }

        if (IsInAnyFraction()) {
            fraction = DZLDatabaseLayer.Get().GetFraction(fractionId);

            if (!fraction) {
                fractionId = "";
            }
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

    string GetActiveJob() {
        if (activeJob == "") {
            activeJob = DAY_Z_LIFE_JOB_CIVIL;
            Save();
        }
        return activeJob;
    }
	
	void SetJobGrade(string grade) {
		activeJobGrade = grade;
		
		if (DAY_Z_LIFE_JOB_COP == activeJob) {
			lastCopRank = activeJobGrade;
		} else if (DAY_Z_LIFE_JOB_MEDIC == activeJob) {
			lastMedicRank = activeJobGrade;
		} else if (DAY_Z_LIFE_JOB_ARMY == activeJob) {
			lastArmyRank = activeJobGrade;
		}
	}

	string GetLastJobRank(string job) {
	    if (DAY_Z_LIFE_JOB_COP == job) {
            return lastCopRank;
        } else if (DAY_Z_LIFE_JOB_MEDIC == job) {
            return lastMedicRank;
        } else if (DAY_Z_LIFE_JOB_ARMY == job) {
            return lastArmyRank;
        }

        return "Rekrut";
	}
	
	string GetJobGrade() {
		return activeJobGrade;
	}

    bool HasJobGrade(string grade) {
        return activeJobGrade == grade;
    }
	
	bool IsActiveAsCop() {
		return DAY_Z_LIFE_JOB_COP == activeJob;
	}

	bool IsActiveAsMedic() {
		return DAY_Z_LIFE_JOB_MEDIC == activeJob;
	}

	bool IsActiveAsArmy() {
		return DAY_Z_LIFE_JOB_ARMY == activeJob;
	}

	bool IsActiveAsCivil() {
		return DAY_Z_LIFE_JOB_CIVIL == activeJob || activeJob == "";
	}
	
	void UpdateActiveJob(string job) {
		activeJob = job;

		if (DAY_Z_LIFE_JOB_COP == job) {
			activeJobGrade = lastCopRank;
		} else if (DAY_Z_LIFE_JOB_MEDIC == job) {
			activeJobGrade = lastMedicRank;
		} else if (DAY_Z_LIFE_JOB_ARMY == job) {
			activeJobGrade = lastArmyRank;
		}

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

    void UpdateCop(bool isCop, string rank) {
        this.isCop = isCop;
        if (isCop) {
            this.lastCopRank = rank;
            if (IsActiveAsCop()) {
               this.activeJobGrade = rank;
            }
        }
        else {
            this.lastCopRank = "";
            ResetJobCivil();
        }

        Save();
    }
	
    void UpdateMedic(bool isMedic, string rank) {
        this.isMedic = isMedic;

        if (isMedic) {
            this.lastMedicRank = rank;
            if (IsActiveAsMedic()) {
               this.activeJobGrade = rank;
            }
        }
        else {
            this.lastMedicRank = "";
            ResetJobCivil();
        }

        Save();
    }
	
    void UpdateArmy(bool isArmy, string rank) {
        this.isArmy = isArmy;

        if (isArmy) {
            this.lastArmyRank = rank;
            if (IsActiveAsArmy()) {
               this.activeJobGrade = rank;
            }
        }
        else {
            this.lastArmyRank = "";
            ResetJobCivil();
        }

        Save();
    }

    private void ResetJobCivil() {
        if (IsActiveAsCivil()) {
           this.activeJobGrade = "Rekrut";
        }
    }

    bool IsCop() {
        return isCop;
    }
	
    bool IsMedic() {
        return isMedic;
    }
    
    bool IsArmy() {
        return isArmy;
    }

    void UpdateName(string playerName) {
        this.playerName = playerName;
        lastLoginDate = new DZLDate();
        Save();
    }

    void LoosPlayerInventoryMoney() {
        money = 0;
        Save();
    }
	
	void AddMoneyToPlayer(int moneyCount) {
        if (GetDayZGame().IsServer()) {
            DZLLogMoneyTransaction(dayZPlayerId, "player", money, money + moneyCount, moneyCount);
			money += moneyCount;
		    Save();
		}
    }

	void AddMoneyToPlayerBank(int moneyCount) {
        if (GetDayZGame().IsServer()) {
            DZLLogMoneyTransaction(dayZPlayerId, "bank", bank, bank + moneyCount, moneyCount);
			bank += moneyCount;
		    Save();
		}
    }

    bool HasEnoughMoney(int amount) {
        return money >= amount;
    }

    bool HasEnoughMoneBank(int amount) {
        return bank >= amount;
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
        DZLLogMoneyTransaction(dayZPlayerId, "has died", money, 0, money * -1);
        money = 0;
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

    void SetBetweenState() {
        deadState = DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_IS_BETWEEN;
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
		items.Init(player, player.GetPosition(), true);

		itemsStore.Insert(items);
        Save();
    }

    DZLStoreItem GetPlayerData() {
        return itemsStore.Get(0);
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

    bool HasBetweenState() {
        return deadState == DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_IS_BETWEEN;
    }

    void TransferFromPlayerToOtherPlayer(DZLPlayer playerTarget) {
        DZLLogMoneyTransaction(dayZPlayerId, "player", money, 0, money * -1);
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

	string CanBuyLicence(notnull DZLCraftLicence licenceToBuy, DZLCraftLicence depLicence){
		if(money < licenceToBuy.price) return "#not_enough_money";
		if(HasLicense(licenceToBuy)) return "#your_already_have_the_licence";

		if (!depLicence) return "";

		if(depLicence && HasDependencyLicense(depLicence)) return "";

		return "#you_have_not_the_dependency_licence";
	}

	bool HasDependencyLicense(notnull DZLCraftLicence depLicence) {
	    return HasLicense(depLicence);
	}
	
	bool HasLicense(DZLCraftLicence licenceToBuy) {
		foreach(string licenceId: licenceIds){
            if(licenceId == licenceToBuy.GetId()){
                return true;
            }
        }
        return false;
	}
	
	void BuyLicence(DZLCraftLicence licenceToBuy){
		money -= licenceToBuy.price;
		licenceIds.Insert(licenceToBuy.GetId());
		Save();
	}

	void AddTicket(int value, string reason) {
		openTickets.Insert(new DZLTicket(value, reason));
		Save();
	}

	array<ref DZLTicket> GetTickets() {
		return openTickets;
	}

	bool HasTickets() {
		return 0 != openTickets.Count();
	}

	void RemoveTicketById(string id) {
		if (!GetGame().IsServer()) return;

		foreach(int index, DZLTicket ticket: openTickets) {
			if (id == ticket.GetId()) {
				openTickets.Remove(index);
				Save();
				return;
			}
		}
	}

	DZLTicket GetTicketById(string id) {
		foreach(int index, DZLTicket ticket: openTickets) {
			if (id == ticket.GetId()) {
				return ticket;
			}
		}
		return null;
	}

	bool IsFractionBoss() {
	    return fractionId == dayZPlayerId;
	}

	bool IsInAnyFraction() {
	    return "" != fractionId;
	}

	DZLFraction GetFraction() {
	    if (GetGame().IsServer()) {
	        fraction = DZLDatabaseLayer.Get().GetFraction(fractionId);
	    }

	    return fraction;
	}

	DZLFractionMember GetFractionMember() {
	    if (fractionId) {
            return GetFraction().GetMember(dayZPlayerId);
	    }
	    return null;
	}

	bool HasFractionRightCanAccessFractionGarage() {
	    return GetFraction() && GetFractionMember().canAccessFractionGarage;
	}

	bool HasFractionRightCanAccessBankAccount() {
	    return GetFraction() && GetFractionMember().canAccessBankAccount;
	}

	bool HasFractionRightCanGetMoneyFromBankAccount() {
	    return GetFraction() && GetFractionMember().canGetMoneyFromBankAccount;
	}

    void RemoveFraction(string fractionId) {
        if (this.fractionId == fractionId) {
            this.fractionId = "";
            fraction = null;

            Save();
        }
    }

    void SetFraction(DZLFraction fraction) {
        this.fraction = fraction;
        this.fractionId = fraction.GetId();
		fractionWherePlayerCanJoin = new array<string>;

        Save();
    }
	
	void UpdateFraction(DZLFraction fraction) {
        if (fractionId != fraction.GetId()) return;
		
        this.fraction = fraction;
        this.fractionId = fraction.GetId();

        Save();
    }	

    void RemovePotentialFraction(string fractionId) {
        foreach(int key, string fractionIdCanJoin: fractionWherePlayerCanJoin) {
            if (fractionId == fractionIdCanJoin) {
                fractionWherePlayerCanJoin.Remove(key);
                break;
            }
        }

        Save();
    }

    void AddPotentialFraction(string fractionId) {
        if (IsInAnyFraction()) return;

        foreach(int key, string fractionIdCanJoin: fractionWherePlayerCanJoin) {
            if (fractionId == fractionIdCanJoin) {
                return;
            }
        }

        fractionWherePlayerCanJoin.Insert(fractionId);

        Save();
    }

    bool HasPotentialFraction(string fractionId) {
        if (IsInAnyFraction()) return false;

        foreach(int key, string fractionIdCanJoin: fractionWherePlayerCanJoin) {
            if (fractionId == fractionIdCanJoin) {
                return true;
            }
        }

        return false;
    }

    string GetFractionId() {
        return fractionId;
    }

    void ResetPotentialFractions() {
        fractionWherePlayerCanJoin = new array<string>;
        Save();
    }

    array<string> GetFractionIdsWherePlayerCanJoin() {
        return fractionWherePlayerCanJoin;
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
            DZLFraction fractionTemp = fraction;
            fraction = null;

            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER);
            DZLJsonFileHandler<DZLPlayer>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, this);
            fraction = fractionTemp;

			return true;
        }
		return false;
    }
}
