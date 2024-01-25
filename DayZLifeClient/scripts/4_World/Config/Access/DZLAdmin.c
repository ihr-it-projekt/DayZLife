class DZLAdmin {
    ref array<ref DZLPlayerAccess> access;
    string version = "6";

    void DZLAdmin() {
        if(!Load()) {
            access = new array<ref DZLPlayerAccess>;
            access.Insert(new DZLPlayerAccess("example Id"));
            version = "6";

            Save();
        }

        if(version == "5") {
            version = "6";

            Save();
        }
    }

    bool CanManagePlayers(string ident) {
        foreach(DZLPlayerAccess playerAccess: access) {
            if(playerAccess && playerAccess.GetIdent() == ident) {
                return playerAccess.CanManagePlayers();
            }
        }
        return false;
    }

    bool CanManageCops(string ident) {
        foreach(DZLPlayerAccess playerAccess: access) {
            if(playerAccess && playerAccess.GetIdent() == ident) {
                return playerAccess.CanManageCops();
            }
        }
        return false;
    }

    bool CanManageMedic(string ident) {
        foreach(DZLPlayerAccess playerAccess: access) {
            if(playerAccess && playerAccess.GetIdent() == ident) {
                return playerAccess.CanManageMedic();
            }
        }
        return false;
    }
    bool CanManageArmy(string ident) {
        foreach(DZLPlayerAccess playerAccess: access) {
            if(playerAccess && playerAccess.GetIdent() == ident) {
                return playerAccess.CanManageArmy();
            }
        }
        return false;
    }

    bool CanManageCars(string ident) {
        foreach(DZLPlayerAccess playerAccess: access) {
            if(playerAccess && playerAccess.GetIdent() == ident) {
                return playerAccess.CanManageCars();
            }
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
