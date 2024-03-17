class DZLFractionMember: DZLNamePlayer {
    string playerId;
    string fractionID;
    string fractionName;
    bool isMember = false;
    bool canAccessBankAccount = false;
    bool canGetMoneyFromBankAccount = false;
    bool canAccessFractionGarage = false;

    bool IsFractionBoss() {
        return fractionID == playerId;
    }
}