class DZLTraderPosition: DZLLicencePosition {
    ref array<string> categoryNames;
    vector spawnPositionOfVehicles;
    vector spawnOrientationOfVehicles;
    string forJob = "";

    bool CanOpenWithJob(string job) {
        if(forJob != "") {
            return job == forJob;
        }

        return true;
    }

}
