class DZLAdmin
{
    ref array<string> adminIds;
	string version = "1";

    void DZLAdmin() {
        if (!Load()) {
            adminIds = new array<string>;

            if (DAY_Z_LIFE_DEBUG) {
                adminIds.Insert("yWqfOC-DbZMpRXQ8NHEL1VPSTG2elJWrU1pMdqSGrN0=");
                adminIds.Insert("f2Yt_of2vfE9XksMJEFwhMiLI1o95ZOTFvt7bKRiwuU=");
            }

            Save();
        }
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
