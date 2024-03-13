class DZLJobHouseDefinition {

    string houseType;
    ref array<string> raidTools;
    int raidTimeInSeconds;
    [NonSerialized()] string jobId;

    void DZLJobHouseDefinition(string houseType, int raidTimeInSeconds = 1200) {
        this.houseType = houseType;
        this.raidTimeInSeconds = raidTimeInSeconds;

        raidTools = new array<string>;
        raidTools.Insert("Crowbar");
    }
}
