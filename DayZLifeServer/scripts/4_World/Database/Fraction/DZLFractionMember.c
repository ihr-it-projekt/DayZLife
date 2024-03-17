modded class DZLFractionMember {

    void DZLFractionMember(string _fractionID, string _playerId, string _name, string _fractionName, bool _isMember) {
        this.fractionID = _fractionID;
        this.playerId = _playerId;
        this.name = _name;
        this.fractionName = _fractionName;
        this.isMember = _isMember;
    }

    void Update(DZLFractionMember member) {
        canAccessBankAccount = member.canAccessBankAccount;
        canGetMoneyFromBankAccount = member.canGetMoneyFromBankAccount;
        canAccessFractionGarage = member.canAccessFractionGarage;
    }
}