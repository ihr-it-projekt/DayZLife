class DZLLicenseActionObject: DZLBaseActionObject {
    void DZLLicenseActionObject() {
        isLicensePoint = true;
    }

    override void SetActions() {
        super.SetActions();

        AddAction(ActionOpenLicenseMenu);
    }
}