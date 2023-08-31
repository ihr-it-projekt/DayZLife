class DZLParkingMeter: DZLBaseActionObject
{
    void DZLParkingMeter() {
		isGarage = true;
	}

	override void SetActions() {
        super.SetActions();

        AddAction(ActionOpenCarStorageMenu);
    }
}