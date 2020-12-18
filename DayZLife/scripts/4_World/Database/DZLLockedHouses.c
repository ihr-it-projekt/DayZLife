class DZLLockedHouses: DZLSaveModel
{
	private ref array<string> houseCollection;

	static void OnServerStart() {
	    DZLLockedHouses houses = DZLDatabaseLayer.Get().GetLockedHouses();
        houses.LockDoors();
	}

    void DZLLockedHouses() {
		if (!Load()) {
	        houseCollection = new array<string>;
			mustSave = true;
		}
    }

    void Add(DZLHouse house) {
        houseCollection.Insert(house.GetFileName());
        mustSave = true;
    }
	
	void Remove(DZLHouse house) {
	    houseCollection.RemoveItem(house.GetFileName());
		mustSave = true;
	}


    void LockDoors() {
        if(!houseCollection) return;
        if (houseCollection.Count() == 0) return;

        foreach(string fileName: houseCollection) {
            DZLHouse house = DZLDatabaseLayer.Get().GetHouse(null, fileName);

            if (!house) continue;
			
            Building building = DZLBuildingHelper.GetBuilding(house);

			if (!building) continue;
			if (!house.GetLockedDoors() || !house.GetLockedDoors().Count() == 0) continue;

            foreach(int doorIndex: house.GetLockedDoors()) {
				if (!building.IsDoorOpen(doorIndex)) {
					building.CloseDoor(doorIndex);
					building.LockDoor(doorIndex);
				    building.UnlockDoor(doorIndex);
				}
			}
        }
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE + LOCKED_HOUSES_FILE_NAME)) {
			JsonFileLoader<DZLLockedHouses>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE + LOCKED_HOUSES_FILE_NAME, this);
			return true;
        }
		return false;
    }

    override protected void DoSave(){
        if (GetGame().IsServer()) {
			CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE);
			DZLJsonFileHandler<DZLLockedHouses>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE + LOCKED_HOUSES_FILE_NAME, this);
		}
    }
}
