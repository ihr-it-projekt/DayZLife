class DZLFractionMember: DZLNamePlayer {

    string playerId;
    string fractionID;
    string fractionName;
    bool isMember = false;
    bool canAccessBankAccount = false;
    bool canGetMoneyFromBankAccount = false;
    bool canAccessFractionGarage = false;

    void DZLFractionMember(string _fractionID, string _playerId, string _name, string _fractionName, bool _isMember) {
        this.fractionID = _fractionID;
        this.playerId = _playerId;
        this.name = _name;
        this.fractionName = _fractionName;
        this.isMember = _isMember;
    }

    bool IsFractionBoss() {
        return fractionID == playerId;
    }
}