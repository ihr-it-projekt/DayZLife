class DZLAdmin {
    private ref array<ref DZLPlayerAccess> access = new array<ref DZLPlayerAccess>();
    private ref array<ref DZLAccess> playerAccesses = new array<ref DZLAccess>();
    string version = "7";

    void DZLAdmin(array<string> jobs) {
        if(version == "6") {
            foreach(DZLPlayerAccess playerAccess: access) {
                DZLAccess access = new DZLAccess(playerAccess.GetIdent(), jobs);

                access.MigrateAccess(playerAccess);

                playerAccesses.Insert(access);
            }

            version = "7";

            Save();
        }
    }

    bool HasAccess(string access, string ident) {
        foreach(DZLAccess playerAccess: playerAccesses) {
            if(!playerAccess) continue;
            if(playerAccess.id != ident) continue;

            return playerAccess.HasAccess(access);

        }
        return false;
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
