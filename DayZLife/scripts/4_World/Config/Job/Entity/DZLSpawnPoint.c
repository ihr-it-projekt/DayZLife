class DZLSpawnPoint
{
    string name;
    vector point;
    vector orientation;
    ref array<string> items;

    void DZLSpawnPoint(string name, vector point, vector orientation, ref array<string> items) {
        this.name = name;
        this.point = point;
        this.orientation = orientation;
        this.items = items;
    }
}
