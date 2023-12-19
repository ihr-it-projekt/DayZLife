class DZLCanDoDoorAction {
    static DZLJobHouseDefinition GetJobHouseDefinition(Building building, notnull PlayerBase player) {
        if (!player.GetConfig()) return null;

        DZLPlayer dzlPlayer =  player.GetDZLPlayer();
        DZLHouseConfig houseConfig = player.GetConfig().houseConfig;
        DZLJobHouseDefinition definition = DZLConfig.Get().houseConfig.GetJobHouseDefinition(building, DAY_Z_LIFE_JOB_COP);

        if (!definition) {
            definition = DZLConfig.Get().houseConfig.GetJobHouseDefinition(building, DAY_Z_LIFE_JOB_ARMY);
        }
        if (!definition) {
            definition = DZLConfig.Get().houseConfig.GetJobHouseDefinition(building, DAY_Z_LIFE_JOB_MEDIC);
        }

        return definition;
    }

    static bool canDoByJob(Building building, PlayerBase player) {
        if (!player.GetConfig()) return false;

        DZLPlayer dzlPlayer =  player.GetDZLPlayer();

        string job = dzlPlayer.GetActiveJob();

        DZLHouseConfig houseConfig = player.GetConfig().houseConfig;

        string jobFromHouse = DAY_Z_LIFE_JOB_COP;
        DZLJobHouseDefinition definition = DZLConfig.Get().houseConfig.GetJobHouseDefinition(building, DAY_Z_LIFE_JOB_COP);

        if (!definition) {
            definition = DZLConfig.Get().houseConfig.GetJobHouseDefinition(building, DAY_Z_LIFE_JOB_ARMY);
            jobFromHouse = DAY_Z_LIFE_JOB_ARMY;
        }
        if (!definition) {
            definition = DZLConfig.Get().houseConfig.GetJobHouseDefinition(building, DAY_Z_LIFE_JOB_MEDIC);
            jobFromHouse = DAY_Z_LIFE_JOB_MEDIC;
        }

        return (definition && job == jobFromHouse) || !definition;
    }


}