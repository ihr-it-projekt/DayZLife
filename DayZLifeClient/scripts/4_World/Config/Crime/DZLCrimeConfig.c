class DZLCrimeConfig {
    private string version = "1";
    int maxMoneyPerTick = 30;
    int minMoneyPerTick = 3;
    int maxMoneyPerRob = 100000;
    ref array<string> robTools;
    bool raidIsCopControlled = false;
    bool raidTimeControlled = false;
    int minCountCopsForRaid = 5;
    int raidStartTimeHour = 16;
    int raidEndTimeHour = 22;
    int raidStartTimeMinute = 0;
    int raidEndTimeMinute = 59;
    int raidDurationTickInSeconds = 60;
    int maxRaidDurationInSeconds = 6000;
    float copAlarmFactorForCopMessage = 0.95;
    int raidCoolDownTimeInSeconds = 1800;
    int maximumRaidDistanceToShop = 20;
    bool canStartRaidIfBankRaidRuns = false;
    bool canUnrestrainSelf = true;
    ref array<ref DZLCrimePosition> shopPosition;


    DZLCrimePosition GetShopByPosition(vector playerPosition, int distance = 2) {
        if(!playerPosition) {
            return null;
        }

        foreach(DZLCrimePosition position: shopPosition) {
            float distanceToPos = vector.Distance(position.position, playerPosition);
            if(distanceToPos <= distance) {
                return position;
            }
        }

        return null;
    }

}