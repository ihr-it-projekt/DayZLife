modded class DZLJobConfig {

    void DZLJobConfig() {
        foreach(string jobName: paycheck.jobNames) {
            loadOuts.Insert(new DZLLoadOuts(jobName));
        }
    }
};