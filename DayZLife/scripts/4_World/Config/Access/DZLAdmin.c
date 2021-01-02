class DZLAdmin
{
    ref array<string> adminIds;
    ref array<ref DZLPlayerAccess> access;
	string version = "2";

    void DZLAdmin() {
        if (!Load()) {
            access = new array<ref DZLPlayerAccess>;
            adminIds = new array<string>;
            version = "2";

            Save();
        }

        if (version == "1") {
            access = new array<ref DZLPlayerAccess>;
            if (adminIds && adminIds.Count() > 0) {
                foreach(string id: adminIds) {
                    access.Insert(new DZLPlayerAccess(id));
                }
            }

            adminIds.Clear();
            version = "2";
            Save();
        }
    }

    bool CanManagePlayers(string ident) {
		foreach(DZLPlayerAccess playerAccess: access) {
        	if (playerAccess && playerAccess.GetIdent() == ident) {
				return playerAccess.CanManagePlayers();
			}
		}
        return false;
    }

    bool CanManageCops(string ident) {
        foreach(DZLPlayerAccess playerAccess: access) {
        	if (playerAccess && playerAccess.GetIdent() == ident) {
				return playerAccess.CanManageCops();
			}
		}
        return false;
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "adminIds.json")) {
            JsonFileLoader<DZLAdmin>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "adminIds.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLAdmin>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "adminIds.json", this);
        }
    }
}
