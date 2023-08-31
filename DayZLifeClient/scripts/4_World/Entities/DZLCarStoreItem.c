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
	bool isInsurance = false;
	string ownerId = "";
	string ownerName = "";

	void DZLCarStoreItem(CarScript item, vector storagePosition, bool withCargo, bool isInsuranceCase) {
		Init(item, storagePosition, withCargo, false);
		isCar = true;
		this.playerAccess = item.playerAccess;
		this.ownerId = item.ownerId;
		this.ownerName = item.ownerName;

		if (!isInsuranceCase) {
			fuel = item.GetFluidFraction(CarFluid.FUEL);
	        oil = item.GetFluidFraction(CarFluid.OIL);
	        brake = item.GetFluidFraction(CarFluid.BRAKE);
	        coolant = item.GetFluidFraction(CarFluid.COOLANT);
	        user1 = item.GetFluidFraction(CarFluid.USER1);
	        user2 = item.GetFluidFraction(CarFluid.USER2);
	        user3 = item.GetFluidFraction(CarFluid.USER3);
	        user4 = item.GetFluidFraction(CarFluid.USER4);
		} else {
			fuel = item.GetFluidCapacity(CarFluid.FUEL);
	        oil = item.GetFluidCapacity(CarFluid.OIL);
	        brake = item.GetFluidCapacity(CarFluid.BRAKE);
	        coolant = item.GetFluidCapacity(CarFluid.COOLANT);
	        user1 = item.GetFluidCapacity(CarFluid.USER1);
	        user2 = item.GetFluidCapacity(CarFluid.USER2);
	        user3 = item.GetFluidCapacity(CarFluid.USER3);
	        user4 = item.GetFluidCapacity(CarFluid.USER4);
		}
		
	}

	bool IsOwner(string playerId) {
        return playerId == ownerId;
	}
}
