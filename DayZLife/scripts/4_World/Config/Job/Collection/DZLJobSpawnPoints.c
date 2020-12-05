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
			    if (jobId == DAY_Z_LIFE_JOB_COP) {
                    items.Insert("CombatKnife");
                    point = new DZLSpawnPoint("Cop", "4620 340 10350", "0 0 0", items);
                    spawnPoints.Insert(point);

                    items = new array<string>;
                    items.Insert("HuntingKnife");
                    point = new DZLSpawnPoint("Military", "4620 340 10330", "0 0 0", items);
                    spawnPoints.Insert(point);

			    } else if (jobId == DAY_Z_LIFE_JOB_MEDIC) {
                    items.Insert("KitchenKnife");
                    point = new DZLSpawnPoint("Sanitäter1", "4620 340 10370", "0 0 0", items);
                    spawnPoints.Insert(point);

                    items = new array<string>;
                    items.Insert("SteakKnife");
                    point = new DZLSpawnPoint("Sanitäter2", "4620 340 10390", "0 0 0", items);
                    spawnPoints.Insert(point);
			    } else {
                    items.Insert("Pickaxe");
                    point = new DZLSpawnPoint("Civil1", "4620 340 10310", "0 0 0", items);
                    spawnPoints.Insert(point);

                    items = new array<string>;
                    items.Insert("Crowbar");
                    point = new DZLSpawnPoint("Civil2", "4620 340 10290", "0 0 0", items);
                    spawnPoints.Insert(point);
			    }
			} else {
			    // TODO
			}
            Save();
        }
    }
	
	
	DZLSpawnPoint FindSpawnById(string id) {
		foreach(DZLSpawnPoint spawnPoint: spawnPoints) {
			if (id == spawnPoint.id) {
				return spawnPoint;
			}
		}
		
		return null;
	}
	

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + jobId + "jobSpawnPoints.json")) {
            JsonFileLoader<DZLJobSpawnPoints>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + jobId + "jobSpawnPoints.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLJobSpawnPoints>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + jobId + "jobSpawnPoints.json", this);
        }
    }
}
