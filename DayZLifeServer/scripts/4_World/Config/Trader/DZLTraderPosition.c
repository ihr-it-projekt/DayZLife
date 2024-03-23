modded class DZLTraderPosition: DZLLicencePosition {

    void DZLTraderPosition(vector _position, vector _orientation, array<string> _categoryNames, vector _spawnPositionOfVehicles, vector _spawnOrientationOfVehicles = "0 0 0", string _forJob = "") {
        Init(_position, _orientation);
        this.categoryNames = _categoryNames;
        this.spawnPositionOfVehicles = _spawnPositionOfVehicles;
        this.spawnOrientationOfVehicles = _spawnOrientationOfVehicles;
        this.forJob = _forJob;
    }
}
