class DZLPaycheck {
    string jobName;
    int amount;
    int onlineMinutesForPay;
    string rank;
    bool isFallbackRank = true;

    void DZLPaycheck(string _jobName, string _rank, int _amount, int _onlineMinutesForPay, bool _isFallbackRank = false) {
        this.jobName = _jobName;
        this.rank = _rank;
        this.amount = _amount;
        this.onlineMinutesForPay = _onlineMinutesForPay;
        isFallbackRank = _isFallbackRank;
    }
}
