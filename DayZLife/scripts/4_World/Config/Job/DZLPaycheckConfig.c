class DZLPaycheckConfig
{
    ref DZLPaycheck cop;
    ref DZLPaycheck medic;
    ref DZLPaycheck civil;
	
	string version = "1";

    void DZLPaycheckConfig() {
        if(!Load()) {
            if (DAY_Z_LIFE_DEBUG) {
                cop = new DZLPaycheck(DAY_Z_LIFE_JOB_COP, 100, 1);
                medic = new DZLPaycheck(DAY_Z_LIFE_JOB_MEDIC, 0, 10000000);
                civil = new DZLPaycheck(DAY_Z_LIFE_JOB_CIVIL, 0, 10000000);
            } else {
                cop = new DZLPaycheck(DAY_Z_LIFE_JOB_COP, 100, 10);
                medic = new DZLPaycheck(DAY_Z_LIFE_JOB_MEDIC, 0, 10000000);
                civil = new DZLPaycheck(DAY_Z_LIFE_JOB_CIVIL, 0, 10000000);
            }
            Save();
        }
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "paycheck.json")) {
            JsonFileLoader<DZLPaycheckConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "paycheck.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLPaycheckConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "paycheck.json", this);
        }
    }
}
