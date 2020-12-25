class DZLJobConfig
{
    ref DZLWorkZones workZones;
    ref DZLPaycheckConfig paycheck;
    ref DZLLoadOuts loadOutsCops;
    ref DZLArrestConfig arrestConfig;

    void DZLJobConfig() {
		workZones = new DZLWorkZones;
        paycheck = new DZLPaycheckConfig;
        loadOutsCops = new DZLLoadOuts(DAY_Z_LIFE_JOB_COP);
        arrestConfig = new DZLArrestConfig;
	}

    DZLWorkZone FindZone(vector playerPosition) {
        if (!playerPosition) {
            return null;
        }

        foreach(DZLWorkZone zone: workZones.workZones) {
            if(vector.Distance(zone.position, playerPosition) <= zone.range) {
                return zone;
            }
        }
        return null;
    }

}
