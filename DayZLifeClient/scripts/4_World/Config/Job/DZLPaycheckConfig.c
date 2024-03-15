class DZLPaycheckConfig {
    string version = "3";

    // Deprecated remove 08.03.25
    private ref array<ref DZLPaycheck>cops;
    private ref array<ref DZLPaycheck>medics;
    private ref array<ref DZLPaycheck>civils;
    private ref array<ref DZLPaycheck>armies;
    // end deprecated

    ref array<string> jobNames = {DAY_Z_LIFE_JOB_COP, DAY_Z_LIFE_JOB_MEDIC, DAY_Z_LIFE_JOB_ARMY};
    ref array<ref DZLJobPayCheck> jobPayChecks = new array<ref DZLJobPayCheck>;

    void DZLPaycheckConfig() {
        if(!Load()) {
            foreach(string jobName: jobNames) {
                jobPayChecks.Insert(new DZLJobPayCheck(jobName));
            }

            Save();
        }
        if("2" == version) {
            jobNames = {DAY_Z_LIFE_JOB_COP, DAY_Z_LIFE_JOB_MEDIC, DAY_Z_LIFE_JOB_ARMY};
            DZLJobPayCheck paycheck = new DZLJobPayCheck(DAY_Z_LIFE_JOB_COP);
            paycheck.MigrateV3(cops);
            jobPayChecks.Insert(paycheck);
            cops = new array<ref DZLPaycheck>;

            paycheck = new DZLJobPayCheck(DAY_Z_LIFE_JOB_MEDIC);
            paycheck.MigrateV3(medics);
            jobPayChecks.Insert(paycheck);
            medics = new array<ref DZLPaycheck>;

            paycheck = new DZLJobPayCheck(DAY_Z_LIFE_JOB_ARMY);
            paycheck.MigrateV3(armies);
            jobPayChecks.Insert(paycheck);
            armies = new array<ref DZLPaycheck>;

            paycheck = new DZLJobPayCheck(DAY_Z_LIFE_JOB_CIVIL);
            paycheck.MigrateV3(civils);
            jobPayChecks.Insert(paycheck);
            civils = new array<ref DZLPaycheck>;

            version = "3";
            Save();
        }

        CheckAllPaychecksExist();
    }

    void CheckAllPaychecksExist() {
        foreach(string jobName: jobNames) {
            bool found = false;
            foreach(DZLJobPayCheck paycheck: jobPayChecks) {
                if(paycheck.jobId == jobName) {
                    found = true;
                    break;
                }
            }
            if(found) continue;
            jobPayChecks.Insert(new DZLJobPayCheck(jobName));
            Save();
        }
    }

    array<ref DZLPaycheck> GetPaycheckByJob(string job) {
        foreach(DZLJobPayCheck paycheck: jobPayChecks) {
            if(paycheck.jobId == job) {
                return paycheck.paychecks;
            }
        }
        return new array<ref DZLPaycheck>;
    }

    DZLPaycheck GetFallbackPaycheckByJob(string job) {
        array<ref DZLPaycheck> collection = GetPaycheckByJob(job);

        foreach(DZLPaycheck paycheck: collection) {
            if(paycheck.isFallbackRank) {
                return paycheck;
            }
        }

        return new DZLPaycheck("", "", 0, 100000000);
    }


    private bool Load() {
        if(GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "paycheck.json")) {
            JsonFileLoader<DZLPaycheckConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "paycheck.json", this);
            return true;
        }
        return false;
    }

    private void Save() {
        if(GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLPaycheckConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "paycheck.json", this);
        }
    }
}
