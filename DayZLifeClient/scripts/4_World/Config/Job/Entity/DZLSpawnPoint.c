class DZLSpawnPoint: DZLBaseSpawnPoint
{
    string name;
    ref array<string> items;

    void DZLSpawnPoint(string name, vector point, vector orientation, ref array<string> items) {
        this.name = name;
        this.items = items;
        Init(point, orientation);
    }
}
