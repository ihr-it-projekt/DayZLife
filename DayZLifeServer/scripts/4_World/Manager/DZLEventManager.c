class DZLEventManager
{
    ref DZLBuyHouseListener buyHouse;
    ref DZLConfigListener config;
    ref DZLPlayerHouseListener playerHouse;
    ref DZLBuyExtensionListener buyExtension;
    ref DZLBankListener bankListener;
    ref DZLBankRaidListener bankRaidListener;
    ref DZLLicenceListener licenceListener;
    ref DZLRaidListener raidListener;
    ref DZLTraderListener traderListener;

    void DZLEventManager() {
        buyHouse = new DZLBuyHouseListener;
        config = new DZLConfigListener;
        playerHouse = new DZLPlayerHouseListener;
        buyExtension = new DZLBuyExtensionListener;
        bankListener = new DZLBankListener;
        bankRaidListener = new DZLBankRaidListener;
        licenceListener = new DZLLicenceListener;
        raidListener = new DZLRaidListener;
        traderListener = new DZLTraderListener;
    }
}
