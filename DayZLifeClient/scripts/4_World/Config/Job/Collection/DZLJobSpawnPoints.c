class DZLJobSpawnPoints {
    string version = "2";
    int blockTimeForJobChange = 3600;
    ref array<ref DZLSpawnPoint> spawnPoints = new array<ref DZLSpawnPoint>;
    [NonSerialized()]string folderPath = "";

    DZLSpawnPoint FindSpawnById(string id) {
        foreach(DZLSpawnPoint spawnPoint: spawnPoints) {
            if(id == spawnPoint.GetId()) {
                return spawnPoint;
            }
        }

        return null;
    }

}
