class DZLBaseActionObject : BuildingSuper {
    bool isBank = false;
    bool isTrader = false;
    bool isGarage = false;
    bool isLicensePoint = false;
    bool isLicenseActionPoint = false;
    bool isShopActionPoint = false;
    bool isTuningPoint = false;
    string jobName;

    bool IsBank() {
        return isBank;
    }

    bool IsTrader() {
        return isTrader;
    }

    bool IsGarage() {
        return isGarage;
    }

    bool IsLicensePoint() {
        return isLicensePoint;
    }

    bool IsLoadOut(string job) {
        return jobName == job;

        SetSynchDirty();
    }

    bool IsLicenseActionPoint() {
        return isLicenseActionPoint;
    }

    bool IsShopActionPoint() {
        return isShopActionPoint;
    }

    bool IsTuningPoint() {
        return isTuningPoint;
    }

}