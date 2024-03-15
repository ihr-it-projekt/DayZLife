class DZLStoragePosition: DZLLicencePosition {
    vector spawnPositionOfVehicles;
    vector spawnOrientationOfVehicles;

    void DZLStoragePosition(vector _position, vector _orientation, vector _spawnPositionOfVehicles, vector _spawnOrientationOfVehicles = "0 0 0") {
        Init(_position, _orientation);
        this.spawnPositionOfVehicles = _spawnPositionOfVehicles;
        this.spawnOrientationOfVehicles = _spawnOrientationOfVehicles;
    }

}
