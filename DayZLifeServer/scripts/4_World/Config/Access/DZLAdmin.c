modded class DZLAdmin {

    void DZLAdmin(array<string> jobs) {
        if(!Load()) Save();

        if(version == "6") {
            foreach(DZLPlayerAccess playerAccess: access) {
                DZLAccess newAccess = new DZLAccess(playerAccess.GetIdent(), jobs);

                newAccess.MigrateAccess(playerAccess);

                playerAccesses.Insert(newAccess);
            }

            version = "7";
            access.Clear();

            Save();
        }
        CheckAllPermissionsExist(jobs);
    }

    void CheckAllPermissionsExist(array<string> jobs) {
        bool hasChange = false;
        foreach(string jobName: jobs) {
            foreach(DZLAccess playerAccess: playerAccesses) {
                if(playerAccess.AddNewAccess(jobName)) hasChange = true;
            }
        }

        if(hasChange) Save();
    }

    private bool Load() {
        if(GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "adminIds.json")) {
            JsonFileLoader<DZLAdmin>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "adminIds.json", this);
            return true;
        }
        return false;
    }

    private void Save() {
        if(GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLAdmin>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "adminIds.json", this);
        }
    }
}