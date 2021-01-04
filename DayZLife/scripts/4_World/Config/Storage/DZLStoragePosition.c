class DZLStoragePosition: DZLLicencePosition
{
    vector spawnPositionOfVehicles;
    vector spawnOrientationOfVehicles;

    void DZLStoragePosition(vector position, vector orientation, string survivor, array<string> attachments, vector spawnPositionOfVehicles, vector spawnOrientationOfVehicles = "0 0 0") {
        Init(position, orientation, survivor, attachments);
        this.spawnPositionOfVehicles = spawnPositionOfVehicles;
        this.spawnOrientationOfVehicles = spawnOrientationOfVehicles;
    }

}
