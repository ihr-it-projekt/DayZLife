modded class DZLPaycheck {

    void DZLPaycheck(string _jobName, string _rank, int _amount, int _onlineMinutesForPay, bool _isFallbackRank = false) {
        this.jobName = _jobName;
        this.rank = _rank;
        this.amount = _amount;
        this.onlineMinutesForPay = _onlineMinutesForPay;
        isFallbackRank = _isFallbackRank;
    }
}
