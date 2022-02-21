class DZLBaseActionObject :BuildingSuper
{
    protected bool isBank = false;
    protected bool isTrader = false;
    protected bool isGarage = false;
    protected bool isCopLoadOut = false;
    protected bool isMedicLoadOut = false;
    protected bool isArmyLoadOut = false;
    protected bool isLicensePoint = false;
    protected bool isLicenseActionPoint = false;
    protected bool isShopActionPoint = false;

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

    bool IsArmyLoadOut() {
        return isArmyLoadOut;
    }

    bool IsLicensePoint() {
        return isLicensePoint;
    }

    bool IsLoadOut() {
        return isCopLoadOut || isMedicLoadOut || isArmyLoadOut;
    }

    bool IsLicenseActionPoint() {
        return isLicenseActionPoint;
    }

    bool IsShopActionPoint() {
        return isShopActionPoint;
    }

}