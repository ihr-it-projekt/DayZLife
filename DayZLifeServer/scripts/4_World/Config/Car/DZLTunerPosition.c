modded class DZLTunerPosition {
    void DZLTunerPosition(vector _position, vector _orientation, array<string> _playerIdsThatCanUsePosition) {
        Init(_position, _orientation);
        this.playerIdsThatCanUsePosition = _playerIdsThatCanUsePosition;
    }
}
