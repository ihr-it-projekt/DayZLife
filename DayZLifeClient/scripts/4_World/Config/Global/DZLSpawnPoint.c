class DZLBaseSpawnPoint: DZLIdModel
{
    vector orientation;
    vector point;

    DZLBaseSpawnPoint Init(vector point, vector orientation) {
        this.orientation = orientation;
        this.point = point;
        SetId();

        return this;
    }
}
