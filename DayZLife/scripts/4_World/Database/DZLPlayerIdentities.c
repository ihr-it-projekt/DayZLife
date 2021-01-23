class DZLPlayerIdentities
{
    string fileName = "DZLPlayerIdentities.json";
    ref array<string> playerIdentities;

    void DZLPlayerIdentities() {
        if (!Load()) {
            playerIdentities = new array<string>;
        }
    }

    void AddPlayer(string playerId) {
        if (-1 == playerIdentities.Find(playerId)) {
            playerIdentities.Insert(playerId);
            Save();
        }
    }
    void RemovePlayer(string playerId) {
		int index = playerIdentities.Find(playerId);
        if (-1 != index) {
            playerIdentities.Remove(index);
            Save();
        }
    }

    array<ref DZLOnlinePlayer> GetCopPlayerCollection() {
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        foreach(string ident: playerIdentities) {
            DZLPlayer player = DZLDatabaseLayer.Get().GetPlayer(ident);

            if (player.IsCop()) {
                collection.Insert(new DZLOnlinePlayer(ident, player.playerName));
            }
        }

        return collection;
    }
	
    array<ref DZLOnlinePlayer> GetMedicPlayerCollection() {
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        foreach(string ident: playerIdentities) {
            DZLPlayer player = DZLDatabaseLayer.Get().GetPlayer(ident);

            if (player.IsMedic()) {
                collection.Insert(new DZLOnlinePlayer(ident, player.playerName));
            }
        }

        return collection;
    }
	
    array<ref DZLOnlinePlayer> GetPlayerCollection(array<string> exclude) {
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        foreach(string ident: playerIdentities) {
            DZLPlayer player = DZLDatabaseLayer.Get().GetPlayer(ident);

            if (exclude.Count() == 0 || exclude.Find(ident) == -1) {
                collection.Insert(new DZLOnlinePlayer(ident, player.playerName));
            }
        }

        return collection;
    }

    void UpdateCops(ref array<string> cops) {
        if (!cops) return;

        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        foreach(string ident: playerIdentities) {
            DZLPlayer player = DZLDatabaseLayer.Get().GetPlayer(ident);
            bool hasFound = false;
            foreach(string newCop: cops) {
                if (ident == newCop) {
                    hasFound = true;
                    break;
                }
            }
            player.UpdateCop(hasFound);
        }
    }
    void UpdateMedics(ref array<string> medics) {
        if (!medics) return;

        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        foreach(string ident: playerIdentities) {
            DZLPlayer player = DZLDatabaseLayer.Get().GetPlayer(ident);
            bool hasFound = false;
            foreach(string newMedic: medics) {
                if (ident == newMedic) {
                    hasFound = true;
                    break;
                }
            }
            player.UpdateMedic(hasFound);
        }
    }

    void UpdateCarKeys(PlayerIdentity player, CarScript car, ref array<string> players) {
        if (!players) return;

        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;
        
        if (!car.IsOwner(player)) return;

        car.UpdatePlayerAccess(players);
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName)) {
            JsonFileLoader<DZLPlayerIdentities>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, this);
            return true;
        }
        return false;
    }

    private bool Save(){
        if (GetGame().IsServer()) {
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER);
            DZLJsonFileHandler<DZLPlayerIdentities>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, this);
			return true;
        }
		return false;
    }

}
