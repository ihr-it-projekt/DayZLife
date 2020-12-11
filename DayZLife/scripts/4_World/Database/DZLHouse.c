class DZLHouse {

    private string fileName;
    private string owner = "";
    private string name = "";
    private vector position;
    private vector orientation;
    private ref array<ref DZLStorageTypeBought> storage;
    private ref DZLHouseExtension alarmSystem;
    private ref array<int> storagePositions;
    private int raidTime = 3;
    private ref array<int> lockedDoors;
    private ref array<string> playerAccess;

    void DZLHouse(Building building = null, string fileName = "") {
        if (building) {
            this.fileName = DZLHouse.GetFileNameFromBuilding(building);;
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
			this.playerAccess = new array<string>;
			Save();
		}
    }
	
	static string GetFileNameFromBuilding(Building building) {
		return building.GetPosition().ToString(false) + ".json";
	}
	
	string GetFileName() {
		return fileName;
	}

	array<int> GetLockedDoors() {
	    return lockedDoors;
	}

	vector GetPosition() {
	    return position;
	}

	string GetName() {
	    return name;
	}
	
	int GetRaidTime() {
		return raidTime;
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
		playerAccess = new array<string>;
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

	void UpdatePlayerAccess(array<string> playerAccess) {
	    this.playerAccess = playerAccess;
	    Save();
	}

	bool HasPlayerAccess(string ident) {
        return -1 != playerAccess.Find(ident);
    }
	
	array<string> GetPlayerAccess() {
		return playerAccess;
	}
	
	bool HasOwner() {
        return owner != "";
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
		DebugMessageDZL("1 " + storagePositions.Count());

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
		return IsDoorLooked(index) && (IsOwner(player) || HasPlayerAccess(player.GetIdentity().GetId()));
	}

	bool CanLookDoor(PlayerBase player, int index) {
		return !IsDoorLooked(index) && (IsOwner(player) || HasPlayerAccess(player.GetIdentity().GetId());
	}

	bool CanRaidDoor(PlayerBase player, int index) {
	    return IsDoorLooked(index) && !IsOwner(player) && !HasPlayerAccess(player.GetIdentity().GetId());
	}
	
	bool HasAlarmSystem() {
		return alarmSystem != null;
	}
	
	DZLHouseExtension GetHouseAlarm() {
		return alarmSystem;
	}

	DZLHouseExtension GetHouseAlarmCast() {
		return DZLHouseAlarm.Cast(alarmSystem);
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
