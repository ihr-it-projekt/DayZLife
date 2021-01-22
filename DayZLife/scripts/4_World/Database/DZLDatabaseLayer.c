class DZLDatabaseLayer
{
    private static ref DZLDatabaseLayer databaseLayer;

    private ref map<string, ref DZLHouse> dzlHouses;
    private ref map<string, ref DZLPlayer> dzlPlayers;
    private ref map<string, ref DZLPlayerHouse> dzlPlayerHouses;
    private ref map<string, ref DZLHouseInventory> dzlHouseInventory;
    private ref DZLPlayerIdentities dzlPlayerIdentities;
    private ref DZLLockedHouses dzlLockedHouses;
    private ref DZLBank bank;
    private ref map<string, ref DZLCarStorage> storageCars;
    private ref DZLEmergencies emergencies;
	private DZLDatabase database;

    void DZLDatabaseLayer() {
        dzlHouses = new map<string, ref DZLHouse>;
        dzlPlayers = new map<string, ref DZLPlayer>;
        dzlPlayerHouses = new map<string, ref DZLPlayerHouse>;
        dzlHouseInventory = new map<string, ref DZLHouseInventory>;
        dzlPlayerIdentities = new DZLPlayerIdentities;
        dzlLockedHouses = new DZLLockedHouses;
        storageCars = new map<string, ref DZLCarStorage>;
        bank = new DZLBank;
        emergencies = new DZLEmergencies;
    }

    static DZLDatabaseLayer Get() {
        if (!databaseLayer) {
            databaseLayer = new DZLDatabaseLayer;
        }

        return databaseLayer;
    }
	
	void SetDatabase(DZLDatabase database) {
		this.database = database;
	}

	DZLBank GetBank() {
	    return bank;
	}

	DZLEmergencies GetEmergencies() {
	    return emergencies;
	}

    DZLLockedHouses GetLockedHouses() {
        return dzlLockedHouses;
    }

    DZLPlayerIdentities GetPlayerIds() {
        return dzlPlayerIdentities;
    }

    bool HasPlayer(string playerId) {
        return database.HasPlayer(playerId);
    }

    DZLPlayer GetPlayerFromFiles(string playerId) {
		DZLPlayer player;
        if (!dzlPlayers.Find(playerId, player)) {
			player = new DZLPlayer(playerId, DZLConfig.Get().bankConfig.startCapital);
			dzlPlayers.Insert(playerId, player);
		}
		
		return player;
    }

    DZLPlayer GetPlayer(string playerId) {
		return database.GetPlayer(playerId);
    }

    DZLHouse GetHouse(Building building = null, string fileNameParam = "") {
        string fileName;
        if (building) {
            fileName = DZLHouse.GetFileNameFromBuilding(building);
        } else {
            fileName = fileNameParam;
        }

        DZLHouse house;
        if(!dzlHouses.Find(fileName, house)) {
            house = new DZLHouse(building, fileName);
            dzlHouses.Insert(fileName, house);
        }

        return house;
    }

    void RemoveHouse(string fileName) {
        DZLHouse house;
        if(dzlHouses.Find(fileName, house)) {
            dzlHouses.Remove(fileName);
            DeleteFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_HOUSE + fileName);
        }
    }

    DZLPlayerHouse GetPlayerHouse(string playerId) {
        DZLPlayerHouse house;
        if (!dzlPlayerHouses.Find(playerId, house)) {
            house = new DZLPlayerHouse(playerId);
            dzlPlayerHouses.Insert(playerId, house);
        }
        return house;
    }

    DZLHouseInventory GetHouseInventory(string playerId, vector position) {
        DZLHouseInventory inventory;
        if (!dzlHouseInventory.Find(playerId + position.ToString(false), inventory)) {
            inventory = new DZLHouseInventory(playerId, position);
            dzlHouseInventory.Insert(playerId + position.ToString(false), inventory);
        }
        return inventory;
    }

    void RemoveHouseInventory(string playerId, vector position) {
        DZLHouseInventory inventory;
        if (!dzlHouseInventory.Find(playerId + position.ToString(false), inventory)) {
            dzlHouseInventory.Remove(playerId);
            inventory.Delete();
        }
    }

    DZLCarStorage GetPlayerCarStorage(string playerId) {
        DZLCarStorage storageCar;
        if (!storageCars.Find(playerId, storageCar)) {
            storageCar = new DZLCarStorage(playerId);
            storageCars.Insert(playerId, storageCar);
        }
        return storageCar;
    }

    void RemovePlayerHouse(string playerId) {
        GetPlayerHouse(playerId);
        DZLPlayerHouse house;
        if (dzlPlayerHouses.Find(playerId, house)) {
            dzlPlayerHouses.Remove(playerId);
			DeleteFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + house.fileName);
        }
    }

    void RemovePlayerCars(string playerId) {
        DZLCarStorage storageCar = GetPlayerCarStorage(playerId);;
        if (storageCars.Find(playerId, storageCar)) {
            storageCars.Remove(playerId);
        }

        DeleteFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_CAR + storageCar.fileName);
    }

    void RemovePlayer(string playerId) {
        database.RemovePlayer(playerId);
    }

}
