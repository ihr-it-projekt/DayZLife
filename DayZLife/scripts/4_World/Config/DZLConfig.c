class DZLConfig
{
    ref DZLMoneyConfig moneyConfig;
    ref DZLHouseConfig houseConfig;
    ref DZLStorageTypes storageTypes;

    void DZLConfig() {
        moneyConfig = new DZLMoneyConfig;
        houseConfig = new DZLHouseConfig;
        storageTypes = new DZLStorageTypes;
    }

}