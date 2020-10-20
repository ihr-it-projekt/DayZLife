class DZLEventManager
{
    ref DZLBuyHouseListener buyHouse;
    ref DZLConfigListener config;
    ref DZLPlayerHouseListener playerHouse;
    ref DZLBuyStorageListener buyStorage;
    ref DZLBankListener bankListener;

    void DZLEventManager() {
        buyHouse = new DZLBuyHouseListener;
        config = new DZLConfigListener;
        playerHouse = new DZLPlayerHouseListener;
        buyStorage = new DZLBuyStorageListener;
        bankListener = new DZLBankListener;
    }
}