class DZLJobSpawnPointCollection {
    string jobId;
    ref DZLJobSpawnPoints spawnPoints;

    void DZLJobSpawnPointCollection(string _jobId) {
        this.jobId = _jobId;
        this.spawnPoints = new DZLJobSpawnPoints(jobId);
    }
}