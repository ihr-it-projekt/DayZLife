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
            ref DZLPlayerHouse playerHouse = new DZLPlayerHouse(player.GetIdentity().GetId());
            playerHouse.AddHouse(house);
        }
    }
    void SellOnServer(PlayerBase player) {
        if(!GetGame().IsClient()){
            house.RemoveOwner();
            ref DZLPlayerHouse playerHouse = new DZLPlayerHouse(player.GetIdentity().GetId());
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
	
	DZLHouseExtension GetHouseAlarm() {
		return house.alarmSystem;
	}

	bool CanBuyAlarm(DZLHouseExtension alarm) {
        if (house.HasAlarmSystem() && alarm.level == house.GetHouseAlarm().level + 1){
            return true;
        } else if (!house.HasAlarmSystem() && alarm.level == 1){
            return true;
        }

        return false;
	}
	
	void SetHouseAlarm(DZLHouseExtension houseAlarm) {
		if(!GetGame().IsClient()){
			house.SetHouseAlarm(houseAlarm);
		}
	}

	void UpdatePlayerAccess(array<string> playerAccess) {
		if(!GetGame().IsClient()){
			house.UpdatePlayerAccess(playerAccess);
		}
	}
	
	array<string> GetPlayerAccess() {
		return house.playerAccess;
	}
	
	bool HasPlayerAccess(string ident) {
		return -1 != house.playerAccess.Find(ident);
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
