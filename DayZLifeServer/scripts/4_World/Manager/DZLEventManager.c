class DZLEventManager
{
    ref DZLBuyHouseListener buyHouse;
    ref DZLConfigListener config;
    ref DZLPlayerHouseListener playerHouse;
    ref DZLBuyStorageListener buyStorage;

    void DZLEventManager() {
        buyHouse = new DZLBuyHouseListener;
        config = new DZLConfigListener;
        playerHouse = new DZLPlayerHouseListener;
        buyStorage = new DZLBuyStorageListener;
    }
}