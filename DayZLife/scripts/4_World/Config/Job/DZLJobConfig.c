class DZLJobConfig
{
    ref DZLWorkZones workZones;
    ref DZLPaycheckConfig paycheck;
    ref DZLLoadOuts loadOutsCops;

    void DZLJobConfig() {
		workZones = new DZLWorkZones;
        paycheck = new DZLPaycheckConfig;
        loadOutsCops = new DZLLoadOuts(DAY_Z_LIFE_JOB_COP);
	}

}
