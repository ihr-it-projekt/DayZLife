class DZLJobHouseDefinition {

    string houseType;
    ref array<string> raidTools;
    int raidTimeInSeconds;
    [NonSerialized()] string jobId;

    void DZLJobHouseDefinition(string _houseType, int _raidTimeInSeconds = 1200) {
        this.houseType = _houseType;
        this.raidTimeInSeconds = _raidTimeInSeconds;

        raidTools = new array<string>;
        raidTools.Insert("Crowbar");
    }
}
