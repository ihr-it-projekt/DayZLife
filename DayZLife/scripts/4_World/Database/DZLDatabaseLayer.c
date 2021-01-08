class DZLDatabaseLayer
{
    private static ref DZLDatabaseLayer databaseLayer;

    private ref map<string, ref DZLHouse> dzlHouses;
    private ref map<string, ref DZLPlayer> dzlPlayers;
    private ref map<string, ref DZLPlayerHouse> dzlPlayerHouses;
    private ref DZLPlayerIdentities dzlPlayerIdentities;
    private ref DZLLockedHouses dzlLockedHouses;
    private ref DZLBank bank;
    private ref map<string, ref DZLCarStorage> storageCars;
    private ref DZLEmergencies emergencies;

    void DZLDatabaseLayer() {
        dzlHouses = new map<string, ref DZLHouse>;
        dzlPlayers = new map<string, ref DZLPlayer>;
        dzlPlayerHouses = new map<string, ref DZLPlayerHouse>;
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
        DZLPlayer player;
        return dzlPlayers.Find(playerId, player);
    }

    DZLPlayer GetPlayer(string playerId) {
		DZLPlayer player;
        if (!dzlPlayers.Find(playerId, player)) {
			player = new DZLPlayer(playerId, DZLConfig.Get().bankConfig.startCapital);
			dzlPlayers.Insert(playerId, player);
		}
		
		return player;
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
        GetPlayerCarStorage(playerId);

        DZLCarStorage storageCar;
        if (storageCars.Find(playerId, storageCar)) {
            storageCars.Remove(playerId);
        }

        DeleteFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + storageCar.fileName);
    }

    void RemovePlayer(string playerId) {
        GetPlayer(playerId);

        DZLPlayer player;
        if (dzlPlayers.Find(playerId, player)) {
            dzlPlayers.Remove(playerId);
			DeleteFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + player.fileName);
		}
    }

}
