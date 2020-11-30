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
            ref DZLPlayerHouse playerHouse = new DZLPlayerHouse(player.GetIdentity());
            playerHouse.AddHouse(house);
        }
    }
    void SellOnServer(PlayerBase player) {
        if(!GetGame().IsClient()){
            house.RemoveOwner();
            ref DZLPlayerHouse playerHouse = new DZLPlayerHouse(player.GetIdentity());
            playerHouse.RemoveHouse(house);
        }
    }
	
	void BuyStorageOnServer(ref DZLStorageTypeBought storage) {
		if(!GetGame().IsClient()){
			house.AddStorage(storage);
		}
	}
	
	void SellStorageOnServer(DZLStorageTypeBought storage) {
		if(!GetGame().IsClient()){
			house.RemoveStorage(storage);
		}
	}
	
	bool HasAlarmSystem() {
		return house.HasAlarmSystem();
	}
	
	DZLHouseAlarm GetHouseAlarm() {
		return house.alarmSystem;
	}

	bool CanBuyAlarm(DZLHouseAlarm alarm) {
	    DebugMessageDZL("Alarm" + alarm.level);
        if (house.HasAlarmSystem() && alarm.level == house.GetHouseAlarm().level + 1){
            return true;
        } else if (!house.HasAlarmSystem() && alarm.level == 1){
            return true;
        }

        return false;
	}
	
	void SetHouseAlarm(DZLHouseAlarm houseAlarm) {
		if(!GetGame().IsClient()){
			house.SetHouseAlarm(houseAlarm);
		}
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
	
	DZLHouse GetDZLHouse() {
		return house;
	}

}
