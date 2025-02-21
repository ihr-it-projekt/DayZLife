modded class DZLJobPayCheck {
    void DZLJobPayCheck(string _jobId) {
        jobId = _jobId;

        paychecks.Insert(new DZLPaycheck(_jobId, "Rekrut", 1000, 30, true));
        paychecks.Insert(new DZLPaycheck(_jobId, "Captian", 2000, 30));
        paychecks.Insert(new DZLPaycheck(_jobId, "Boss", 3000, 30));
    }

    void MigrateV3(array<ref DZLPaycheck> _paychecks) {
        paychecks = _paychecks;
    }
}