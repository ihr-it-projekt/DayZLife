modded class DZLFraction {


    void DZLFraction(string playerId, string _name = "") {
        id = playerId;
        Init(DAY_Z_LIFE_SERVER_FOLDER_DATA_FRACTION, playerId + "fraction");
        if(LoadJSON(playerId + "fraction.json")) {
            Init(DAY_Z_LIFE_SERVER_FOLDER_DATA_FRACTION, playerId + "fraction");
            Save();
        }

        Init(DAY_Z_LIFE_SERVER_FOLDER_DATA_FRACTION, playerId + "fraction");
        if(!Load()) {
            name = _name;
            Save();
        }
    }

    void RemoveMember(string playerId) {
        foreach(int key, DZLFractionMember member: members) {
            if(member.playerId == playerId) {
                members.Remove(key);
                return
            }
        }
    }
    void RemovePotentialMember(string playerId) {
        foreach(int key, DZLFractionMember member: potentialMembers) {
            if(member.playerId == playerId) {
                potentialMembers.Remove(key);
                return
            }
        }
    }

    void AddMember(ref DZLFractionMember member) {
        if(HasMember(member.playerId)) return;
        members.Insert(member);
    }

    void AddPotentialMember(ref DZLFractionMember member) {
        if(HasPotentialMember(member.playerId)) return;
        potentialMembers.Insert(member);
    }

    void UpdateMember(DZLFractionMember member) {
        DZLFractionMember memberFromDb = GetMember(member.playerId);
        if(memberFromDb) memberFromDb.Update(member);
    }

    void AddMoney(int money) {
        bankAccount += money;

        Save();
    }

    void DepositMoneyFromFractionToOtherPlayer(DZLPlayer playerTarget, int moneyToTransfer) {
        playerTarget.AddMoneyToPlayerBank(moneyToTransfer);

        if(moneyToTransfer > 0) {
            DZLLogMoneyTransaction(id, "fraction", bankAccount, bankAccount - moneyToTransfer, moneyToTransfer * -1);
            bankAccount -= moneyToTransfer;
        }

        Save();
    }

    override protected bool Read(FileSerializer ctx) {
        if(!ctx.Read(version)) return false;
        if(!ctx.Read(name)) return false;
        if(!ctx.Read(id)) return false;
        if(!ctx.Read(members)) return false;
        if(!ctx.Read(potentialMembers)) return false;
        if(!ctx.Read(bankAccount)) return false;

        return true;
    }

    override protected void Write(FileSerializer ctx) {
        ctx.Write(version);
        ctx.Write(name);
        ctx.Write(id);
        ctx.Write(members);
        ctx.Write(potentialMembers);
        ctx.Write(bankAccount);
    }

    private bool LoadJSON(string tmpFileName) {
        if(FileExist(path + tmpFileName + ".json")) {
            JsonFileLoader<DZLFraction>.JsonLoadFile(path + tmpFileName + ".json", this);
            DeleteFile(path + tmpFileName + ".json");
            return true;
        }
        return false;
    }

}
