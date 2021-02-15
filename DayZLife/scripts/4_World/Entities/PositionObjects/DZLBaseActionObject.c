class DZLBaseActionObject :BuildingSuper
{

    protected bool isBank = false;
    protected bool isTrader = false;
    protected bool isGarage = false;
    protected bool isCopLoadOut = false;
    protected bool isMedicLoadOut = false;
    protected bool isLicensePoint = false;

    bool IsBank() {
        return isBank;
    }

    bool IsTrader() {
        return isTrader;
    }

    bool IsGarage() {
        return isGarage;
    }

    bool IsCopLoadOut() {
        return isCopLoadOut;
    }

    bool IsMedicLoadOut() {
        return isMedicLoadOut;
    }

    bool IsLicensePoint() {
        return isLicensePoint;
    }

    bool IsLoadOut() {
        return isCopLoadOut || isMedicLoadOut;
    }

}