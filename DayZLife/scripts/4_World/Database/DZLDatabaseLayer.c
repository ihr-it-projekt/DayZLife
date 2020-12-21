

class DZLDatabaseLayer
{
    private static ref DZLDatabaseLayer databaseLayer;

    private ref map<string, ref DZLHouse> dzlHouses;
    private ref map<string, ref DZLPlayer> dzlPlayers;
    private ref map<string, ref DZLPlayerHouse> dzlPlayerHouses;
    private ref DZLPlayerIdentities dzlPlayerIdentities;
    private ref DZLLockedHouses dzlLockedHouses;
    private ref DZLBank bank;

    void DZLDatabaseLayer() {
        dzlHouses = new map<string, ref DZLHouse>;
        dzlPlayers = new map<string, ref DZLPlayer>;
        dzlPlayerHouses = new map<string, ref DZLPlayerHouse>;
        dzlPlayerIdentities = new DZLPlayerIdentities;
        dzlLockedHouses = new DZLLockedHouses;
        bank = new DZLBank;
    }

    void Save() {
        dzlPlayerIdentities.Save();
        dzlLockedHouses.Save();
        bank.Save();

        foreach(DZLHouse house: dzlHouses) {
            house.Save();
        }
		
        foreach(DZLPlayer player: dzlPlayers) {
            player.Save();
        }
        foreach(DZLPlayerHouse playerHouse: dzlPlayerHouses) {
            playerHouse.Save();
        }
    }

    static DZLDatabaseLayer Get() {
        if (!databaseLayer) {
            databaseLayer = new DZLDatabaseLayer;
			DebugMessageDZL("create new databaseLayer");
        }

        return databaseLayer;
    }

	DZLBank GetBank() {
	    return bank;
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

    DZLPlayer GetPlayer(string playerId, int moneyToAdd = 0) {
		DZLPlayer player;
        if (!dzlPlayers.Find(playerId, player)) {
			player = new DZLPlayer(playerId, moneyToAdd);
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

    void RemovePlayerHouse(string playerId) {
        DZLPlayerHouse house;
        if (dzlPlayerHouses.Find(playerId, house)) {
            dzlPlayerHouses.Remove(playerId);
			DeleteFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + house.fileName);
        }
    }

    void RemovePlayer(string playerId) {
        DZLPlayer player;
        if (dzlPlayers.Find(playerId, player)) {
            dzlPlayers.Remove(playerId);
			DeleteFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + player.fileName);
		}
    }

}
