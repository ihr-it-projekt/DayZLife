class DZLCanDoDoorAction {
    static DZLJobHouseDefinition GetJobHouseDefinition(Building building, notnull PlayerBase player) {
        DZLHouseConfig houseConfig = DZLConfig.Get().houseConfig;
        if(!houseConfig) return null;

        DZLPlayer dzlPlayer = player.GetDZLPlayer();
        return houseConfig.GetJobHouseDefinition(building);
    }

    static bool canDoByJob(Building building, PlayerBase player) {
        DZLHouseConfig houseConfig = DZLConfig.Get().houseConfig;
        if(!houseConfig) return false;

        DZLPlayer dzlPlayer = player.GetDZLPlayer();
        string job = dzlPlayer.GetActiveJob();

        DZLJobHouseDefinition definition = houseConfig.GetJobHouseDefinition(building);

        return definition && job == definition.jobId;
    }

    static bool IsJobDoor(Building building) {
        DZLHouseConfig houseConfig = DZLConfig.Get().houseConfig;
        if(!houseConfig) return false;

        DZLJobHouseDefinition definition = houseConfig.GetJobHouseDefinition(building);

        return !!definition;
    }
}