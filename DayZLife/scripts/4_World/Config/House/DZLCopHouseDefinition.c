class DZLCopHouseDefinition {
	
   	string houseType;
	int raidRange;
	ref array<string> raidTools;
	int raidTimeInSeconds; 

    void DZLCopHouseDefinition(string houseType, int raidRange = 10, int raidTimeInSeconds = 60) {
        this.houseType = houseType;
        this.raidRange = raidRange;
        this.raidTimeInSeconds = raidTimeInSeconds;

        raidTools = new array<string>;
        raidTools.Insert("Crowbar");
    }
}
