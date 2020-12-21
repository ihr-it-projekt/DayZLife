class DZLHouse: DZLSaveModel
{

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
            this.fileName = DZLHouse.GetFileNameFromBuilding(building);
        } else {
            this.fileName = fileName;
        }

		if (!Load() && building) {
	        this.name = building.GetType();
			this.position = building.GetPosition();
			this.orientation = building.GetOrientation();
			this.storage = new array<ref DZLStorageTypeBought>;
			this.storagePositions = new array<int>;
			this.lockedDoors = new array<int>;
			this.playerAccess = new array<string>;
			mustSave = true;
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
        lockedDoors = new array<int>;
        alarmSystem = null;
        storagePositions = new array<int>;
        playerAccess = new array<string>;
        mustSave = true;
    }
	
	bool IsOwner(PlayerBase player) {
		return owner == player.GetIdentity().GetId();
	}
	
	void RemoveOwner() {
		owner = "";
		this.lockedDoors = new array<int>;
		alarmSystem = null;
		storagePositions = new array<int>;
		playerAccess = new array<string>;
		mustSave = true;
	}
	
	void AddStorage(ref DZLStorageTypeBought storageItem) {
		storage.Insert(storageItem);
		mustSave = true;
	}
	
	void RemoveStorage(DZLStorageTypeBought storageItem) {
		storage.RemoveItem(storageItem);
		mustSave = true;
	}

	void UpdatePlayerAccess(array<string> playerAccess) {
	    this.playerAccess = playerAccess;
	    mustSave = true;
	}

	bool HasPlayerAccess(string ident) {
        return -1 != playerAccess.Find(ident);
    }
	
	void RemovePlayerAccess(string ident) {
        int index = playerAccess.Find(ident);
		if (index != -1) {
			playerAccess.Remove(index);
			mustSave = true;
		}
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
		mustSave = true;
	}
	
	void LockDoor(int doorIndex) {
		lockedDoors.Insert(doorIndex);
		mustSave = true;
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

	void SetHouseAlarm(DZLHouseExtension houseAlarm) {
		alarmSystem = houseAlarm;
		mustSave = true;
	}

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE + fileName)) {
			JsonFileLoader<DZLHouse>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE + fileName, this);
			return true;
        }
		return false;
    }

    override protected void DoSave(){
        if (GetGame().IsServer()) {
			CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE);
			DZLJsonFileHandler<DZLHouse>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE + fileName, this);
		}
    }
}
