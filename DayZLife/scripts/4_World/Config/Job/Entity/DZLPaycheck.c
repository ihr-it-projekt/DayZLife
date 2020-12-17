class DZLPaycheck
{
    string jobName;
    int amount;
    int onlineMinutesForPay;

    void DZLPaycheck(string jobName,int amount, int onlineMinutesForPay) {
        this.jobName = jobName;
        this.amount = amount;
        this.onlineMinutesForPay = onlineMinutesForPay;
    }
}
