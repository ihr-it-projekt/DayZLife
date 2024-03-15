class DZLTunerPosition: DZLLicencePosition {
    ref array<string>playerIdsThatCanUsePosition;

    void DZLTunerPosition(vector _position, vector _orientation, array<string> _playerIdsThatCanUsePosition) {
        Init(_position, _orientation);
        this.playerIdsThatCanUsePosition = _playerIdsThatCanUsePosition;
    }

    bool PlayerCanDoActions(string id) {
        foreach(string playerId: playerIdsThatCanUsePosition) {
            if(id == playerId) {
                return true;
            }
        }
        return false;
    }
}
