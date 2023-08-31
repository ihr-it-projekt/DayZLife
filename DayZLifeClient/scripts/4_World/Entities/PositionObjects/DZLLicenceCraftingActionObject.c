class DZLLicenceCraftingActionObject: DZLBaseActionObject
{
    void DZLLicenceCraftingActionObject() {
		isLicenseActionPoint = true;
	}

	override void SetActions() {
        super.SetActions();

        AddAction(ActionLicenceCrafting);
    }
}