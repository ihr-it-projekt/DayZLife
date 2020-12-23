class DZLServerLicence
{
    private static ref DZLServerLicence licence;

    private string licenceKey = "free";
	private string version = "1";

	static DZLServerLicence Get() {
        if (!licence) {
            licence = new DZLServerLicence;
        }

        return licence;
    }
	
	string GetLicenceKey() {
		return licenceKey;
	}

    void DZLServerLicence() {
        if (!Load()) {
            Save();
        }
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "ServerLicenceFile.json")) {
            JsonFileLoader<DZLServerLicence>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "ServerLicenceFile.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLServerLicence>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "ServerLicenceFile.json", this);
        }
    }
}
