class DZLLicenceConfig
{
	ref array<ref DZLLicence> licences;
	
	
	void DZLLicenceConfig() {
        if (!Load()) {
			licences = new array<ref DZLLicence>;
			licences.Insert(new DZLLicence(100, "Cement Licence", "12310 140 12633", 20));
			licences.Insert(new DZLLicence(100, "Cement Licence 2", "12310 140 12633", 20, "Cement Licence"));
			
			Save();
		}
	}
	
	private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "licence.json")) {
            JsonFileLoader<DZLLicenceConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "licence.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLLicenceConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "licence.json", this);
        }
    }

}