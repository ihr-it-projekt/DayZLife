class DZLJobConfig {
    ref DZLWorkZones workZones;
    ref DZLPaycheckConfig paycheck;
    ref DZLLoadOuts loadOutsTransport;
    ref DZLLoadOuts loadOutsCops;
    ref DZLLoadOuts loadOutsMedics;
    ref DZLLoadOuts loadOutsArmy;
    ref DZLArrestConfig arrestConfig;

    void DZLJobConfig() {
        workZones = new DZLWorkZones;
        paycheck = new DZLPaycheckConfig;
        loadOutsCops = new DZLLoadOuts(DAY_Z_LIFE_JOB_COP);
        loadOutsTransport = new DZLLoadOuts(DAY_Z_LIFE_JOB_TRANSPORT);
        loadOutsMedics = new DZLLoadOuts(DAY_Z_LIFE_JOB_MEDIC);
        loadOutsArmy = new DZLLoadOuts(DAY_Z_LIFE_JOB_ARMY);
        arrestConfig = new DZLArrestConfig;
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