class DZLEventManager
{
    ref DZLBuyHouseListener buyHouse;
    ref DZLConfigListener config;
    ref DZLPlayerHouseListener playerHouse;

    void DZLEventManager() {
        buyHouse = new DZLBuyHouseListener;
        config = new DZLConfigListener;
        playerHouse = new DZLPlayerHouseListener;
    }
}