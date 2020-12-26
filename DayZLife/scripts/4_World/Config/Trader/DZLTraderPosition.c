class DZLTraderPosition: DZLLicencePosition
{
    ref array<string> categoryNames;
    vector spawnPositionOfVehicles;
    vector spawnOrientationOfVehicles;
    string forJob = "";

    void DZLTraderPosition(vector position, vector orientation, string survivor, array<string> attachments, array<string> categoryNames, vector spawnPositionOfVehicles, vector spawnOrientationOfVehicles = "0 0 0", string forJob = "") {
        Init(position, orientation, survivor, attachments);
        this.categoryNames = categoryNames;
        this.spawnPositionOfVehicles = spawnPositionOfVehicles;
        this.spawnOrientationOfVehicles = spawnOrientationOfVehicles;
        this.forJob = forJob;
    }

    bool CanOpenWithJob(string job) {
        if (forJob != "") {
            return job == forJob;
        }

        return true;
    }

}
