class DZLStoragePosition: DZLLicencePosition {
    vector spawnPositionOfVehicles;
    vector spawnOrientationOfVehicles;

    void DZLStoragePosition(vector position, vector orientation, vector spawnPositionOfVehicles, vector spawnOrientationOfVehicles = "0 0 0") {
        Init(position, orientation);
        this.spawnPositionOfVehicles = spawnPositionOfVehicles;
        this.spawnOrientationOfVehicles = spawnOrientationOfVehicles;
    }

}
