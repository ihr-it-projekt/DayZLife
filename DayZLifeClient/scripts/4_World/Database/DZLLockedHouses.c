class DZLLockedHouses {
    private ref array<string> houseCollection;

    static void OnServerStart() {
        DZLLockedHouses houses = DZLDatabaseLayer.Get().GetLockedHouses();
        houses.LockDoors();
    }

    void DZLLockedHouses() {
        if (!Load()) {
            houseCollection = new array<string>;
            Save();
        }
    }

    void Add(DZLHouse house) {
        if (-1 == houseCollection.Find(house.GetFileName())) {
            houseCollection.Insert(house.GetFileName());
            Save();
        }
    }

    void Remove(DZLHouse house) {
        int index = houseCollection.Find(house.GetFileName());
        if (index != -1) {
            houseCollection.Remove(index);
            Save();
        }
    }


    void LockDoors() {
        if(!houseCollection) return;
        if (houseCollection.Count() == 0) return;

        foreach(string fileName: houseCollection) {
            DZLHouse house = DZLDatabaseLayer.Get().GetHouse(null, fileName);

            if (!house) continue;

            Building building = DZLBuildingHelper.GetBuilding(house);

            if (!building) {
                continue;
            }

            if (!house.GetLockedDoors()) {
                continue;
            }

            if (house.GetLockedDoors().Count() == 0) {
                continue;
            }
            array<int> doors = house.GetLockedDoors();
            foreach(int doorIndex: doors) {
                if (!building.IsDoorOpen(doorIndex)) {
                    building.CloseDoor(doorIndex);
                    building.LockDoor(doorIndex);
                    building.UnlockDoor(doorIndex);
                }
            }
        }
    }

    private bool Load() {
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE + LOCKED_HOUSES_FILE_NAME)) {
            JsonFileLoader<DZLLockedHouses>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE + LOCKED_HOUSES_FILE_NAME, this);
            return true;
        }
        return false;
    }

    private bool Save() {
        if (GetGame().IsServer()) {
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE);
            DZLJsonFileHandler<DZLLockedHouses>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE + LOCKED_HOUSES_FILE_NAME, this);
            return true;
        }
        return false;
    }
}
