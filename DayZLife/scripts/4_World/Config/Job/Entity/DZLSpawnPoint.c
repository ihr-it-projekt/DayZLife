class DZLSpawnPoint
{
    vector point;
    vector orientation;
    ref array<string> items;

    void DZLSpawnPoint(vector point, vector orientation, ref array<string> items) {
        this.point = point;
        this.orientation = orientation;
        this.items = items;
    }
}
