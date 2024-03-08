class DZLJobNames {
    ref array<string> jobNames = {DAY_Z_LIFE_JOB_COP, DAY_Z_LIFE_JOB_TRANSPORT, DAY_Z_LIFE_JOB_MEDIC, DAY_Z_LIFE_JOB_ARMY};

    private bool Load() {
        if(GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "jobNames.json")) {
            JsonFileLoader<DZLJobNames>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "jobNames.json", this);
            return true;
        }
        return false;
    }

    private void Save() {
        if(GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLJobNames>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "jobNames.json", this);
        }
    }
}
