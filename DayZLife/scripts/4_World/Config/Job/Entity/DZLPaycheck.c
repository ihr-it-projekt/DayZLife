class DZLPaycheck
{
    string jobName;
    int amount;
    int onlineMinutesForPay;
    string rang;
    bool isFallbackRang = true;

    void DZLPaycheck(string jobName, string rang, int amount, int onlineMinutesForPay) {
        this.jobName = jobName;
        this.rang = rang;
        this.amount = amount;
        this.onlineMinutesForPay = onlineMinutesForPay;
        isFallbackRang = true;
    }
}
