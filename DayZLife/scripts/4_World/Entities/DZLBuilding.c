class DZLBuilding {

    private Building building;
    private ref DZLHouse house;

    void DZLBuilding(Building building) {
        this.building = building;
        house = new DZLHouse(building);
    }

    bool HasOwner() {
        return house.owner != "";
    }

    bool IsOwner(PlayerBase player) {
        return house.owner == player.GetIdentity().GetId();
    }

    void BuyOnServer(PlayerBase player) {
        if(!GetGame().IsClient()){
            house.AddOwner(player);
            ref DZLPlayerHouse playerHouse = new DZLPlayerHouse(player);
            playerHouse.AddHouse(house);
        }
    }
    void SellOnServer(PlayerBase player) {
        if(!GetGame().IsClient()){
            house.RemoveOwner();
            ref DZLPlayerHouse playerHouse = new DZLPlayerHouse(player);
            playerHouse.RemoveHouse(house);
        }
    }
	
	void BuyStorageOnServer(ref DZLStorageTypeBought storage) {
		house.AddStorage(storage);
	}
	
	void SellStorageOnServer(DZLStorageTypeBought storage) {
		house.RemoveStorage(storage);
	}
	
	vector GetNextFreeStoragePosition(DZLHouseDefinition definition) {
		return house.GetNextFreeStoragePosition(definition);
	}
	
	DZLStorageTypeBought FindStorageByPosition(vector position) {
		return house.FindStorageByPosition(position);
	}

    array<ref DZLStorageTypeBought> GetStorage() {
       return house.GetStorage();
    }

}