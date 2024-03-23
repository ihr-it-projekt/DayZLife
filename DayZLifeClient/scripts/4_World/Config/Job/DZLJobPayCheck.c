class DZLJobPayCheck {
    string jobId;
    ref array<ref DZLPaycheck> paychecks = new array<ref DZLPaycheck>();

    void DZLPaycheck(string _jobName, string _rank, int _amount, int _onlineMinutesForPay, bool _isFallbackRank = false) {}
}