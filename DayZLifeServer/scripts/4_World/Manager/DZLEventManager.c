class DZLEventManager
{
    ref DZLBuyHouseListener buyHouse;
    ref DZLConfigListener config;

    void DZLEventManager() {
        buyHouse = new DZLBuyHouseListener;
        config = new DZLConfigListener;
    }
}