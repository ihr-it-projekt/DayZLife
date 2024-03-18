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
}
