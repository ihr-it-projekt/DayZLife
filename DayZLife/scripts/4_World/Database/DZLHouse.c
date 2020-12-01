class DZLHouse {

    string fileName;
    string owner = "";
    string name = "";
	vector position;
	vector orientation;
	ref array<ref DZLStorageTypeBought> storage;
	ref DZLHouseExtension alarmSystem;
	ref array<int> storagePositions;
	int raidTime = 3;
	ref array<int> lockedDoors;

    void DZLHouse(Building building = null, string fileName = "") {
        if (building) {
            this.fileName = DZLHouse.GetFileName(building);;
        } else {
            this.fileName = fileName;
        }

		if (!Load()) {
	        this.name = building.GetType();
			this.position = building.GetPosition();
			this.orientation = building.GetOrientation();
			this.storage = new array<ref DZLStorageTypeBought>;
			this.storagePositions = new array<int>;
			this.lockedDoors = new array<int>;
			Save();
		}
    }
	
	static string GetFileName(Building building) {
		return building.GetPosition().ToString(false) + ".json";
	}

    void AddOwner(PlayerBase player) {
        owner = player.GetIdentity().GetId();
        Save();
    }
	
	bool IsOwner(PlayerBase player) {
		return owner == player.GetIdentity().GetId();
	}
	
	void RemoveOwner() {
		owner = "";
		this.lockedDoors = new array<int>;
		alarmSystem = null;
		Save();
	}
	
	void AddStorage(ref DZLStorageTypeBought storageItem) {
		storage.Insert(storageItem);
		Save();
	}
	
	void RemoveStorage(DZLStorageTypeBought storageItem) {
		storage.RemoveItem(storageItem);
		Save();
	}
	
	int GetCountStorage() {
		return storage.Count();
	}
	
	bool HasStorage() {
		return GetCountStorage() != 0;
	}

	array<ref DZLStorageTypeBought> GetStorage() {
	    return storage;
	}
	
	vector GetNextFreeStoragePosition(DZLHouseDefinition definition) {
		array<vector> storagePositions = definition.storagePosition;
		foreach(vector pos: storagePositions) {
			bool notFound = true;
			
			foreach(DZLStorageTypeBought storageObject: storage) {
				if (storageObject.relativePos == pos) {
					notFound = false;
					break;
				}
			}
			
			if (notFound) {
				return pos;
			}
		} 
		return "0 0 0";
	}
	
	DZLStorageTypeBought FindStorageByPosition(vector position) {
		foreach(DZLStorageTypeBought storageObject: storage) {
			if (storageObject.position == position) {
				return storageObject;
			}
		}
		return null;	
	}
	
	bool IsDoorLooked(int doorIndex) {
		return -1 < lockedDoors.Find(doorIndex);
	}
	
	void UnLookDoor(int doorIndex) {
		lockedDoors.RemoveItem(doorIndex);
		Save();
	}
	
	void LockDoor(int doorIndex) {
		lockedDoors.Insert(doorIndex);
		Save();
	}
	
	bool CanUnLookDoor(PlayerBase player, int index) {
		return IsDoorLooked(index) && IsOwner(player);
	}

	bool CanLookDoor(PlayerBase player, int index) {
		return !IsDoorLooked(index) && IsOwner(player);
	}

	bool CanRaidDoor(PlayerBase player, int index) {
		return IsDoorLooked(index) && !IsOwner(player);
	}
	
	bool HasAlarmSystem() {
		return !!alarmSystem;
	}
	
	DZLHouseExtension GetHouseAlarm() {
		return alarmSystem;
	}
	
	void SetHouseAlarm(DZLHouseExtension houseAlarm) {
		alarmSystem = houseAlarm;
		Save();
	}

	string GetAlarmMessage(PlayerBase player) {
	    string alarmMessage = "";
	    if (alarmSystem) {
	        if (alarmSystem.level == 1) {
	            alarmMessage = alarmSystem.message;
	        } else if (alarmSystem.level == 2) {
	            alarmMessage = alarmSystem.message + name;
	        } else if (alarmSystem.level == 3) {
	            alarmMessage = alarmSystem.message + name  + "/" + player.GetIdentity().GetName();
	        }
	    }

	    return alarmMessage;
	}
	
    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE + fileName)) {
			JsonFileLoader<DZLHouse>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE + fileName, this);
			return true;
        }
		return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
			CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE);
			DZLJsonFileHandler<DZLHouse>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE + fileName, this);
		}
    }
}
