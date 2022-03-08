class DZLFraction
{
	private string version = "1";
	private string fileName;
	private string name;
	private string id;
	private ref array<ref DZLFractionMember> members;
	private ref array<ref DZLFractionMember> potentialMembers;
	private int bankAccount = 0;

    void DZLFraction(string playerId, string name = "") {
        fileName = playerId + "fraction.json";
        id = playerId;

        if (!Load()) {
            members = new array<ref DZLFractionMember>;
            potentialMembers = new array<ref DZLFractionMember>;
            this.name = name;

            Save();
        }
    }
	
	string GetId() {
		return id;
	}

    void RemoveMember(string playerId) {
        foreach(int key, DZLFractionMember member: members) {
            if (member.playerId == playerId) {
                members.Remove(key);
                return
            }
        }
    }
    void RemovePotentialMember(string playerId) {
        foreach(int key, DZLFractionMember member: potentialMembers) {
            if (member.playerId == playerId) {
                potentialMembers.Remove(key);
                return
            }
        }
    }

    void AddMember(ref DZLFractionMember member) {
        if (HasMember(member.playerId)) return;
        members.Insert(member);
    }

    void AddPotentialMember(ref DZLFractionMember member) {
        if (HasPotentialMember(member.playerId)) return;
        potentialMembers.Insert(member);
    }

    DZLFractionMember GetMember(string playerId) {
        foreach(int key, DZLFractionMember member: members) {
            if (member.playerId == playerId) {
                return member;
            }
        }

        return null,
    }

    bool HasPotentialMember(string playerId) {
        foreach(int key, DZLFractionMember member: potentialMembers) {
            if (member.playerId == playerId) {
                return true;
            }
        }

        return false,
    }

    bool HasMember(string playerId) {
        foreach(int key, DZLFractionMember member: members) {
            if (member.playerId == playerId) {
                return true;
            }
        }

        return false,
    }

    ref array<ref DZLFractionMember> GetMembers() {
        return members;
    }

    ref array<ref DZLFractionMember> GetPotentialMembers() {
        return potentialMembers;
    }

    void UpdateMember(DZLFractionMember member) {
        DZLFractionMember memberFromDb = GetMember(member.playerId);

        if (memberFromDb) {
            memberFromDb.Update(member);
        }
    }

    string GetName() {
        return name;
    }

    int GetBankAccount() {
        return bankAccount;
    }

    void AddMoney(int money) {
        bankAccount += money;

        Save();
    }

	void DepositMoneyFromFractionToOtherPlayer(DZLPlayer playerTarget, int moneyToTransfer) {
	    playerTarget.AddMoneyToPlayerBank(moneyToTransfer);

		if (moneyToTransfer > 0) {
		    DZLLogMoneyTransaction(id, "fraction", bankAccount, bankAccount - moneyToTransfer, moneyToTransfer * -1);
			bankAccount -= moneyToTransfer;
		}

		Save();
	}

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_FRACTION + fileName)) {
            JsonFileLoader<DZLFraction>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_FRACTION + fileName, this);
            return true;
        }
        return false;
    }

    bool Save(){
        if (GetGame().IsServer()) {
			CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_FRACTION);
			DZLJsonFileHandler<DZLFraction>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_FRACTION + fileName, this);
			return true;
        }
		return false;
    }

    void Delete() {
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_FRACTION + fileName)) {
            DeleteFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_FRACTION + fileName);
        }
    }
}
