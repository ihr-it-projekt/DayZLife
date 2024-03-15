class DZLCanDoDoorAction {
    static DZLJobHouseDefinition GetJobHouseDefinition(Building building, notnull PlayerBase player) {
        DZLHouseConfig houseConfig = DZLConfig.Get().houseConfig;
        if(!houseConfig) return null;

        DZLPlayer dzlPlayer = player.GetDZLPlayer();
        return houseConfig.GetJobHouseDefinition(building);
    }

    static bool canDoByJob(Building building, PlayerBase player, int doorIndex) {
        DZLHouseConfig houseConfig = DZLConfig.Get().houseConfig;
        if(!houseConfig) return false;

        DZLPlayer dzlPlayer = player.GetDZLPlayer();
        string job = dzlPlayer.GetActiveJob();

        DZLJobHouseDefinition definition = houseConfig.GetJobHouseDefinition(building);

#ifdef TBRealEstateClient
        BuildingBase buildingBase = BuildingBase.Cast(building);
        if(buildingBase.TBREIsBuildingActiveSellBuilding()) {
            if(buildingBase.TBREIsDoorLooked(doorIndex)) return false;
        }
#endif

        return (definition && job == definition.jobId) || !definition;
    }


}