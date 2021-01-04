class DZLCarStoreItem: DZLStoreItem
{
	ref array<string> playerAccess;

	float fuel;
	float oil;
	float brake;
	float coolant;
	float user1;
	float user2;
	float user3;
	float user4;

	void DZLCarStoreItem(CarScript item, vector storagePosition) {
		Init(item, storagePosition, false);
		isCar = true;
		this.playerAccess = item.playerAccess;

		fuel = item.GetFluidFraction(CarFluid.FUEL);
        oil = item.GetFluidFraction(CarFluid.OIL);
        brake = item.GetFluidFraction(CarFluid.BRAKE);
        coolant = item.GetFluidFraction(CarFluid.COOLANT);
        user1 = item.GetFluidFraction(CarFluid.USER1);
        user2 = item.GetFluidFraction(CarFluid.USER2);
        user3 = item.GetFluidFraction(CarFluid.USER3);
        user4 = item.GetFluidFraction(CarFluid.USER4);
	}
}
