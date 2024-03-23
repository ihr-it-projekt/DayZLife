class DZLBaseSpawnPoint: DZLIdModel {
    vector orientation;
    vector point;

    DZLBaseSpawnPoint Init(vector _point, vector _orientation) {
        this.orientation = _orientation;
        this.point = _point;
        SetId();

        return this;
    }
}
