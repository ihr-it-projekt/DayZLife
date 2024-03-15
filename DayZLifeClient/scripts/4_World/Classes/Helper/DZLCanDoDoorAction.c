class DZLCanDoDoorAction {
    static DZLJobHouseDefinition GetJobHouseDefinition(Building building, notnull PlayerBase player) {
        if(!player.GetDZLConfig()) return null;

        DZLPlayer dzlPlayer = player.GetDZLPlayer();
        DZLHouseConfig houseConfig = player.GetDZLConfig().houseConfig;

        if(!houseConfig) return null;

        return houseConfig.GetJobHouseDefinition(building);
    }

    static bool canDoByJob(Building building, PlayerBase player, int doorIndex) {
        if(!player.GetDZLConfig()) return false;

        DZLPlayer dzlPlayer = player.GetDZLPlayer();

        string job = dzlPlayer.GetActiveJob();

        DZLHouseConfig houseConfig = player.GetDZLConfig().houseConfig;
        if(!houseConfig) return false;

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