class DZLEventManager {
    ref DZLBuyHouseListener buyHouse;
    ref DZLConfigListener config;
    ref DZLPlayerHouseListener playerHouse;
    ref DZLBuyExtensionListener buyExtension;
    ref DZLBankListener bankListener;
    ref DZLLicenceListener licenceListener;
    ref DZLRaidListener raidListener;
    ref DZLTraderListener traderListener;
    ref DZLPlayerSpawnListener spawnPointListener;
    ref DZLAlmanacListener almanacListener;
    ref DZLLoadOutListener loadOutListener;
    ref DZLPlayerArrestListener arrestListener;
    ref DZLHarvestListener harvestListener;
    ref DZLCarKeyListener carKeyListener;
    ref DZLStorageListener carStorageListener;
    ref DZLMedicHelpListener medicHelpListener;
    ref DZLMessageListener messageListener;
    ref DZLShopRaidListener shopRaidListener;
    ref DZLPlayerTicketListener playerTicketListener;
    ref DZLFractionListener fractionListener;
    ref DZLTuningListener tuningListener;

    void DZLEventManager() {
        buyHouse = new DZLBuyHouseListener;
        config = new DZLConfigListener;
        playerHouse = new DZLPlayerHouseListener;
        buyExtension = new DZLBuyExtensionListener;
        bankListener = new DZLBankListener;
        licenceListener = new DZLLicenceListener;
        raidListener = new DZLRaidListener;
        traderListener = new DZLTraderListener;
        spawnPointListener = new DZLPlayerSpawnListener;
        almanacListener = new DZLAlmanacListener;
        loadOutListener = new DZLLoadOutListener;
        arrestListener = new DZLPlayerArrestListener;
        harvestListener = new DZLHarvestListener;
        carKeyListener = new DZLCarKeyListener;
        carStorageListener = new DZLStorageListener;
        medicHelpListener = new DZLMedicHelpListener;
        messageListener = new DZLMessageListener;
        shopRaidListener = new DZLShopRaidListener;
        playerTicketListener = new DZLPlayerTicketListener;
        fractionListener = new DZLFractionListener;
        tuningListener = new DZLTuningListener;
    }
}
