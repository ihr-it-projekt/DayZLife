class DZLTraderPosition: DZLLicencePosition
{
    ref array<string> categoryNames;
    vector spawnPositionOfVehicles;
    vector spawnOrientationOfVehicles;
    void DZLTraderPosition(vector position, vector orientation, string survivor, array<string> attachments, array<string> categoryNames, vector spawnPositionOfVehicles, vector spawnOrientationOfVehicles = "0 0 0") {
        Init(position, orientation, survivor, attachments);
        this.categoryNames = categoryNames;
        this.spawnPositionOfVehicles = spawnPositionOfVehicles;
        this.spawnOrientationOfVehicles = spawnOrientationOfVehicles;
    }

}
