class DZLJobConfig {
    ref DZLWorkZones workZones = new DZLWorkZones;
    ref DZLPaycheckConfig paycheck = new DZLPaycheckConfig;

    // deprecated remove 08.03.2025
    private ref DZLLoadOuts loadOutsCops;
    private ref DZLLoadOuts loadOutsMedics;
    private ref DZLLoadOuts loadOutsArmy;
    // deprecated end

    private ref array<ref DZLLoadOuts> loadOuts = new array<ref DZLLoadOuts>;
    ref DZLArrestConfig arrestConfig = new DZLArrestConfig;

    DZLLoadOuts GetLoadOuts(string jobName) {
        foreach(DZLLoadOuts loadOut: loadOuts) {
            if(loadOut.jobId == jobName) return loadOut;
        }

        return new DZLLoadOuts("");
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