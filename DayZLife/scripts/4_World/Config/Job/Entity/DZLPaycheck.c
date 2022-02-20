class DZLPaycheck
{
    string jobName;
    int amount;
    int onlineMinutesForPay;
    string rank;
    bool isFallbackRank = true;

    void DZLPaycheck(string jobName, string rank, int amount, int onlineMinutesForPay) {
        this.jobName = jobName;
        this.rank = rank;
        this.amount = amount;
        this.onlineMinutesForPay = onlineMinutesForPay;
        isFallbackRank = true;
    }
}
