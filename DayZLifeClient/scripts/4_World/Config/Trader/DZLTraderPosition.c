class DZLTraderPosition: DZLLicencePosition {
    ref array<string> categoryNames;
    vector spawnPositionOfVehicles;
    vector spawnOrientationOfVehicles;
    string forJob = "";

    void DZLTraderPosition(vector _position, vector _orientation, array<string> _categoryNames, vector _spawnPositionOfVehicles, vector _spawnOrientationOfVehicles = "0 0 0", string _forJob = "") {
        Init(_position, _orientation);
        this.categoryNames = _categoryNames;
        this.spawnPositionOfVehicles = _spawnPositionOfVehicles;
        this.spawnOrientationOfVehicles = _spawnOrientationOfVehicles;
        this.forJob = _forJob;
    }

    bool CanOpenWithJob(string job) {
        if(forJob != "") {
            return job == forJob;
        }

        return true;
    }

}
