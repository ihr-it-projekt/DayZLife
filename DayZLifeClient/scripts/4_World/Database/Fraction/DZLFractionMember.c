class DZLFractionMember: DZLNamePlayer {
    string playerId;
    string fractionID;
    string fractionName;
    bool isMember = false;
    bool canAccessBankAccount = false;
    bool canGetMoneyFromBankAccount = false;
    bool canAccessFractionGarage = false;

    void DZLFractionMember(string fractionID, string playerId, string name, string fractionName, bool isMember) {
        this.fractionID = fractionID;
        this.playerId = playerId;
        this.name = name;
        this.fractionName = fractionName;
        this.isMember = isMember;
    }

    void Update(DZLFractionMember member) {
        canAccessBankAccount = member.canAccessBankAccount;
        canGetMoneyFromBankAccount = member.canGetMoneyFromBankAccount;
        canAccessFractionGarage = member.canAccessFractionGarage;
    }

    bool IsFractionBoss() {
        return fractionID == playerId;
    }
}