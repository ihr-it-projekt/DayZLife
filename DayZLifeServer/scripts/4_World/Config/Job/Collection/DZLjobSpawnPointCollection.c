modded class DZLJobSpawnPointCollection {
    void DZLJobSpawnPointCollection(string _jobId) {
        this.jobId = _jobId;
        this.spawnPoints = new DZLJobSpawnPoints(jobId);
    }
}