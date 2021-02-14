class DZLBaseActionObject :BuildingSuper
{

    private bool isBank = false;
    private bool isTrader = false;
    private bool isGarage = false;
    private bool isCopLoadOut = false;
    private bool isMedicLoadOut = false;
    private bool isLicensePoint = false;

    void EnableBank() {
        RegisterNetSyncVariableBool("isBank");
        isBank = true;
    }

    bool IsBank() {
        return isBank;
    }

    void EnableTrader() {
        RegisterNetSyncVariableBool("isTrader");
        isTrader = true;
    }

    bool IsTrader() {
        return isTrader;
    }

    void EnableGarage() {
        RegisterNetSyncVariableBool("isGarage");
        isGarage = true;
    }

    bool IsGarage() {
        return isGarage;
    }

    void EnableCopLoadOut() {
        RegisterNetSyncVariableBool("isCopLoadOut");
        isCopLoadOut = true;
    }

    bool IsCopLoadOut() {
        return isCopLoadOut;
    }

    void EnableMedicLoadOut() {
        RegisterNetSyncVariableBool("isMedicLoadOut");
        isMedicLoadOut = true;
    }

    bool IsMedicLoadOut() {
        return isMedicLoadOut;
    }

    void EnableLicensePoint() {
        RegisterNetSyncVariableBool("isLicensePoint");
        isLicensePoint = true;
    }

    bool IsLicensePoint() {
        return isLicensePoint;
    }

    bool IsLoadOut() {
        return isCopLoadOut || isMedicLoadOut;
    }

    override void SetActions()
    {
        super.SetActions();

        AddAction(ActionOpenBankingMenu);
        AddAction(ActionRobBank);
        AddAction(DZLActionPaybackRobtMoney);
        AddAction(ActionOpenTraderMenu);
        AddAction(ActionOpenLoadOutMenu);
        AddAction(ActionOpenCarStorageMenu);
        AddAction(ActionOpenLicenseMenu);
    }
}