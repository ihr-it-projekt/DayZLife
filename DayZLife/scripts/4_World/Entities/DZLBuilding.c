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
	
	void BuyStorageOnServer(DZLStorageTypeBought storage) {
		house.AddStorage(storage);
	}
	
	void SellStorageOnServer(DZLStorageTypeBought storage) {
		house.RemoveStorage(storage);
	}

    array<ref DZLStorageTypeBought> GetStorage() {
       return house.GetStorage();
    }

}