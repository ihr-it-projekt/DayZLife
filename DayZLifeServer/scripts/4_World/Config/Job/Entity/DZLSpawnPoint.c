modded class DZLSpawnPoint: DZLBaseSpawnPoint {

    void DZLSpawnPoint(string _name, vector _point, vector _orientation, ref array<string> _items) {
        this.name = _name;
        this.items = _items;
        Init(_point, _orientation);
    }
}
