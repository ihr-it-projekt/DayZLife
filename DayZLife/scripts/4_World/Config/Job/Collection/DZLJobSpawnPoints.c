class DZLJobSpawnPoints
{
    string jobId;
    ref array<ref DZLSpawnPoint> spawnPoints;

    void DZLJobSpawnPoints(string jobId) {
        this.jobId = jobId;
        if (!Load()) {
            spawnPoints = new array<ref DZLSpawnPoint>;
			DZLSpawnPoint point
			array<string> items = new array<string>;
						
			if (DAY_Z_LIFE_DEBUG) {
				items.Insert("");
				
				point = new DZLSpawnPoint("","",items);
				
				spawnPoints.Insert(point);
			} else {
			
			}
			
	
			
            
            Save();
        }
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + jobId + "jobSpawnPoints.json")) {
            JsonFileLoader<DZLJobSpawnPoints>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + jobId + "jobSpawnPoints.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        jobSpawnPoints = null;
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLJobSpawnPoints>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + jobId + "jobSpawnPoints.json", this);
        }
    }
}
