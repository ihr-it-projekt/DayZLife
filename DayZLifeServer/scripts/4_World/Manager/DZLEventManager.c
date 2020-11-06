class DZLEventManager
{
    ref DZLBuyHouseListener buyHouse;
    ref DZLConfigListener config;
    ref DZLPlayerHouseListener playerHouse;
    ref DZLBuyStorageListener buyStorage;
    ref DZLBankListener bankListener;
    ref DZLBankRaidListener bankRaidListener;
    ref DZLLicenceListener licenceListener;
    ref DZLRaidListener raidListener;

    void DZLEventManager() {
        buyHouse = new DZLBuyHouseListener;
        config = new DZLConfigListener;
        playerHouse = new DZLPlayerHouseListener;
        buyStorage = new DZLBuyStorageListener;
        bankListener = new DZLBankListener;
        bankRaidListener = new DZLBankRaidListener;
        licenceListener = new DZLLicenceListener;
        raidListener = new DZLRaidListener;
    }
}