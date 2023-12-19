class DZLTunerPosition: DZLLicencePosition {
    ref array<string>playerIdsThatCanUsePosition;

    void DZLTunerPosition(vector position, vector orientation, array<string> playerIdsThatCanUsePosition) {
        Init(position, orientation);
        this.playerIdsThatCanUsePosition = playerIdsThatCanUsePosition;
    }

    bool PlayerCanDoActions(string id) {
        foreach(string playerId: playerIdsThatCanUsePosition) {
            if (id == playerId) {
                return true;
            }
        }
        return false;
    }
}
