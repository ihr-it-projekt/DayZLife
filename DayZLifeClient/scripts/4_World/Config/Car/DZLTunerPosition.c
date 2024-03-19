class DZLTunerPosition: DZLLicencePosition {
    ref array<string>playerIdsThatCanUsePosition;

    bool PlayerCanDoActions(string id) {
        foreach(string playerId: playerIdsThatCanUsePosition) {
            if(id == playerId) {
                return true;
            }
        }
        return false;
    }
}
