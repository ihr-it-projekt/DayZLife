modded class DZLMedicConfig {

    void DZLMedicConfig() {
        if(!Load()) {
            DZLBaseSpawnPoint point = new DZLBaseSpawnPoint();
            hospitalSpawnPoints.Insert(point.Init("10283.518555 12.801783 2293.035400", "46.999985 0.000000 0.000000"));
            point = new DZLBaseSpawnPoint();
            hospitalSpawnPoints.Insert(point.Init("6478.244629 9.735042 2713.157715", "-162.000000 0.000000 0.000000"));
            point = new DZLBaseSpawnPoint();
            hospitalSpawnPoints.Insert(point.Init("3767.240234 312.504150 9011.118164", "-27.000000 0.000000 0.000000"));
            Save();
        }
        if(version == "1") {
            version = "2";
            deleteDeadBodyTimeWhenHealedByMedic = 5;
            Save();
        }
        if(version == "2") {
            version = "3";

            minTimeBeforeHospital = 600;
            minTimeBeforeHospitalWhenMinMedicNotOnline = 300;
            minTimeBeforeKillButton = 20;
            minMedicCountForHospitalTimer = 1;
            Save();
        }
    }

    private bool Load() {
        if(FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "medic.json")) {
            JsonFileLoader<DZLMedicConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "medic.json", this);
            return true;
        }
        return false;
    }

    private void Save() {
        CheckDZLConfigPath();
        JsonFileLoader<DZLMedicConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "medic.json", this);
    }
}
