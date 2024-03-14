class DZLJobConfig {
    ref DZLWorkZones workZones = new DZLWorkZones;
    ref DZLPaycheckConfig paycheck = new DZLPaycheckConfig;

    // deprecated remove 08.03.2025
    private ref DZLLoadOuts loadOutsCops = new DZLLoadOuts(DAY_Z_LIFE_JOB_COP);
    private ref DZLLoadOuts loadOutsMedics = new DZLLoadOuts(DAY_Z_LIFE_JOB_MEDIC);
    private ref DZLLoadOuts loadOutsArmy = new DZLLoadOuts(DAY_Z_LIFE_JOB_ARMY);
    // deprecated end

    private ref array<ref DZLLoadOuts> loadOuts = new array<ref DZLLoadOuts>;
    ref DZLArrestConfig arrestConfig = new DZLArrestConfig;

    void DZLJobConfig() {
        foreach(string jobName: paycheck.jobNames) {
            loadOuts.Insert(new DZLLoadOuts(jobName));
        }
    }

    DZLLoadOuts GetLoadOuts(string jobName) {
        foreach(DZLLoadOuts loadOut: loadOuts) {
            if(loadOut.jobId == jobName) return loadOut;
        }

        return new DZLLoadOuts(jobName);
    }


    DZLWorkZone FindZone(vector playerPosition) {
        if(!playerPosition) {
            return null;
        }

        foreach(DZLWorkZone zone: workZones.workZones) {
            if(vector.Distance(zone.position, playerPosition) <= zone.range) {
                return zone;
            }
        }
        return null;
    }
};