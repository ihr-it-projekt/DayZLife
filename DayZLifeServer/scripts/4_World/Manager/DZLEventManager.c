class DZLEventManager {
    ref DZLConfigListener config;
    ref DZLBankListener bankListener;
    ref DZLLicenceListener licenceListener;
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
        config = new DZLConfigListener;
        bankListener = new DZLBankListener;
        licenceListener = new DZLLicenceListener;
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
