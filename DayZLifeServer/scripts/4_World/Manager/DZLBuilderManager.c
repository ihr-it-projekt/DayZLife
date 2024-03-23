class DZLBuilderManager {
    private static ref DZLBuilderManager instance;

    static DZLBuilderManager Get() {
        if(!instance) {
            instance = new DZLBuilderManager;
        }

        return instance;
    }

    private ref DZLBankingLocationBuilder bankingBuilder = new DZLBankingLocationBuilder();
    private ref DZLLicenceLocationBuilder licenceBuilder = new DZLLicenceLocationBuilder();
    private ref DZLTraderLocationBuilder traderBuilder = new DZLTraderLocationBuilder();
    private ref DZLLoadOutLocationBuilder loadOutBuilder = new DZLLoadOutLocationBuilder();
    private ref DZLGarageLocationBuilder garageBuilder = new DZLGarageLocationBuilder();
    private ref DZLShopLocationBuilder shopBuilder = new DZLShopLocationBuilder();
    private ref DZLTuningLocationBuilder tuningBuilder = new DZLTuningLocationBuilder();

    private ref Timer checkTimer = new Timer;


    void Reload() {
        bankingBuilder.Reload();
        licenceBuilder.Reload();
        traderBuilder.Reload();
        loadOutBuilder.Reload();
        garageBuilder.Reload();
        shopBuilder.Reload();
        tuningBuilder.Reload();
    }

    void Create() {
        bankingBuilder.Create();
        licenceBuilder.Create();
        traderBuilder.Create();
        loadOutBuilder.Create();
        garageBuilder.Create();
        shopBuilder.Create();
        tuningBuilder.Create();
    }
}
