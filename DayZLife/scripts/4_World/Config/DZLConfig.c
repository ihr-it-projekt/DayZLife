class DZLConfig
{
    ref DZLMoneyConfig moneyConfig;
    ref DZLHouseConfig houseConfig;

    void DZLConfig() {
        moneyConfig = new DZLMoneyConfig;
        houseConfig = new DZLHouseConfig;
    }

}