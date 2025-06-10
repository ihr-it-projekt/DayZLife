class DZLFraction: DZLFileSerializer {
    protected string version = "1";
    protected string name;
    protected string id;
    protected ref array<ref DZLFractionMember> members = new array<ref DZLFractionMember>;
    protected ref array<ref DZLFractionMember> potentialMembers = new array<ref DZLFractionMember>;
    protected int bankAccount = 0;

    string GetId() {
        return id;
    }

    DZLFractionMember GetMember(string playerId) {
        if(playerId == id) {
            DZLFractionMember boss = new DZLFractionMember(id, id, "", name, true);
            boss.canAccessBankAccount = true;
            boss.canGetMoneyFromBankAccount = true;
            boss.canAccessFractionGarage = true;

            return boss;
        }
        foreach(int key, DZLFractionMember member: members) {
            if(member.playerId == playerId) {
                return member;
            }
        }

        return null;
    }

    bool HasPotentialMember(string playerId) {
        foreach(int key, DZLFractionMember member: potentialMembers) {
            if(member.playerId == playerId) {
                return true;
            }
        }

        return false;
    }

    bool HasMember(string playerId) {
        foreach(int key, DZLFractionMember member: members) {
            if(member.playerId == playerId) {
                return true;
            }
        }

        return false;
    }

    array<ref DZLFractionMember> GetMembers() {
        return members;
    }

    array<ref DZLFractionMember> GetPotentialMembers() {
        return potentialMembers;
    }

    string GetName() {
        return name;
    }

    int GetBankAccount() {
        return bankAccount;
    }

}
