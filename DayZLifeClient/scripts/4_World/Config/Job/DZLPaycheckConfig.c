class DZLPaycheckConfig {
    string version = "2";
    ref DZLPaycheck cop;
    ref DZLPaycheck transport;
    ref DZLPaycheck medic;
    ref DZLPaycheck civil;

    ref array<ref DZLPaycheck>cops;
    ref array<ref DZLPaycheck>transports;
    ref array<ref DZLPaycheck>medics;
    ref array<ref DZLPaycheck>civils;
    ref array<ref DZLPaycheck>armies;


    void DZLPaycheckConfig() {
        if(!Load()) {
            cops = new array<ref DZLPaycheck>;
            cops.Insert(new DZLPaycheck(DAY_Z_LIFE_JOB_COP, "Rekrut", 100, 1));

            medics = new array<ref DZLPaycheck>;
            medics.Insert(new DZLPaycheck(DAY_Z_LIFE_JOB_MEDIC, "Rekrut", 0, 10000000));

            transports = new array<ref DZLPaycheck>;
            transports.Insert(new DZLPaycheck(DAY_Z_LIFE_JOB_TRANSPORT, "Rekrut", 0, 10000000));

            civils = new array<ref DZLPaycheck>;
            civils.Insert(new DZLPaycheck(DAY_Z_LIFE_JOB_CIVIL, "Rekrut", 0, 10000000));

            armies = new array<ref DZLPaycheck>;
            armies.Insert(new DZLPaycheck(DAY_Z_LIFE_JOB_ARMY, "Rekrut", 0, 10000000));

            Save();
        } else if("1" == version) {
            cops = new array<ref DZLPaycheck>;
            cop.isFallbackRank = true;
            cop.rank = "Rekrut";
            cops.Insert(cop);

            transports = new array<ref DZLPaycheck>;
            transport.isFallbackRank = true;
            transport.rank = "Rekrut";
            transports.Insert(transport);

            medics = new array<ref DZLPaycheck>;
            medic.isFallbackRank = true;
            cop.rank = "Rekrut";
            medics.Insert(medic);

            civils = new array<ref DZLPaycheck>;
            civil.isFallbackRank = true;
            cop.rank = "Rekrut";
            civils.Insert(civil);

            armies = new array<ref DZLPaycheck>;
            armies.Insert(new DZLPaycheck(DAY_Z_LIFE_JOB_ARMY, "Rekrut", 0, 10000000));

            version = "2";
            cop = null;
            medic = null;
            civil = null;

            Save();
        }
    }

    array<ref DZLPaycheck> GetPaycheckByJob(string job) {
        if(DAY_Z_LIFE_JOB_MEDIC == job) {
            return medics;
        }

        if(DAY_Z_LIFE_JOB_TRANSPORT == job) {
            return transports;
        }

        if(DAY_Z_LIFE_JOB_COP == job) {
            return cops;
        }

        if(DAY_Z_LIFE_JOB_ARMY == job) {
            return armies;
        }

        return civils;
    }

    DZLPaycheck GetFallbackPaycheckByJob(string job) {
        if(DAY_Z_LIFE_JOB_MEDIC == job) {
            return GetFallbackFromCollection(medics);
        }

        if(DAY_Z_LIFE_JOB_TRANSPORT == job) {
            return GetFallbackFromCollection(transports);
        }

        if(DAY_Z_LIFE_JOB_COP == job) {
            return GetFallbackFromCollection(cops);
        }

        if(DAY_Z_LIFE_JOB_ARMY == job) {
            return GetFallbackFromCollection(armies);
        }

        return GetFallbackFromCollection(civils);
    }

    private DZLPaycheck GetFallbackFromCollection(array<ref DZLPaycheck> collection) {
        foreach(DZLPaycheck paycheck: collection) {
            if(paycheck.isFallbackRank) {
                return paycheck;
            }
        }

        return null;
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
