class DZLPlayerIdentities {
    string fileName = "DZLPlayerIdentities.json";
    ref array<string> playerIdentities;

    void DZLPlayerIdentities() {
        if(!Load()) {
            playerIdentities = new array<string>;
        }
    }

    void AddPlayer(string playerId) {
        if(-1 == playerIdentities.Find(playerId)) {
            playerIdentities.Insert(playerId);
            Save();
        }
    }
    void RemovePlayer(string playerId) {
        int index = playerIdentities.Find(playerId);
        if(-1 != index) {
            playerIdentities.Remove(index);
            Save();
        }
    }

    array<ref DZLOnlinePlayer> GetCopPlayerCollection() {
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        foreach(string ident: playerIdentities) {
            DZLPlayer player = DZLDatabaseLayer.Get().GetPlayer(ident);

            if(player.IsCop()) {
                collection.Insert(new DZLOnlinePlayer(ident, player.playerName, player.GetLastJobRank(DAY_Z_LIFE_JOB_COP)));
            }
        }

        return collection;
    }
	
	array<ref DZLOnlinePlayer> GetTransportPlayerCollection() {
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        foreach(string ident: playerIdentities) {
            DZLPlayer player = DZLDatabaseLayer.Get().GetPlayer(ident);

            if(player.IsTransport()) {
                collection.Insert(new DZLOnlinePlayer(ident, player.playerName, player.GetLastJobRank(DAY_Z_LIFE_JOB_TRANSPORT)));
            }
        }

        return collection;
    }

    array<ref DZLOnlinePlayer> GetMedicPlayerCollection() {
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        foreach(string ident: playerIdentities) {
            DZLPlayer player = DZLDatabaseLayer.Get().GetPlayer(ident);

            if(player.IsMedic()) {
                collection.Insert(new DZLOnlinePlayer(ident, player.playerName, player.GetLastJobRank(DAY_Z_LIFE_JOB_MEDIC)));
            }
        }

        return collection;
    }

    array<ref DZLOnlinePlayer> GetArmyPlayerCollection() {
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        foreach(string ident: playerIdentities) {
            DZLPlayer player = DZLDatabaseLayer.Get().GetPlayer(ident);

            if(player.IsArmy()) {
                collection.Insert(new DZLOnlinePlayer(ident, player.playerName, player.GetLastJobRank(DAY_Z_LIFE_JOB_ARMY)));
            }
        }

        return collection;
    }

    array<ref DZLOnlinePlayer> GetPlayerCollection(array<string> exclude) {
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        foreach(string ident: playerIdentities) {
            DZLPlayer player = DZLDatabaseLayer.Get().GetPlayer(ident);

            if(exclude.Count() == 0 || exclude.Find(ident) == -1) {
                collection.Insert(new DZLOnlinePlayer(ident, player.playerName, ""));
            }
        }

        return collection;
    }

    void UpdateCops(ref array<DZLOnlinePlayer> cops) {
        if(!cops) return;

        foreach(string ident: playerIdentities) {
            DZLPlayer player = DZLDatabaseLayer.Get().GetPlayer(ident);
            bool hasFound = false;
            string newRank = "";
            foreach(DZLOnlinePlayer newCop: cops) {
                if(ident == newCop.id) {
                    hasFound = true;
                    newRank = newCop.rank;
                    break;
                }
            }

            player.UpdateCop(hasFound, newRank);
        }
    }
	
	void UpdateTransports(ref array<DZLOnlinePlayer> transports) {
        if(!transports) return;

        foreach(string ident: playerIdentities) {
            DZLPlayer player = DZLDatabaseLayer.Get().GetPlayer(ident);
            bool hasFound = false;
            string newRank = "";
            foreach(DZLOnlinePlayer newTransport: transports) {
                if(ident == newTransport.id) {
                    hasFound = true;
                    newRank = newTransport.rank;
                    break;
                }
            }

            player.UpdateTransport(hasFound, newRank);
        }
    }

    void UpdateMedics(ref array<DZLOnlinePlayer> medics) {
        if(!medics) return;

        foreach(string ident: playerIdentities) {
            DZLPlayer player = DZLDatabaseLayer.Get().GetPlayer(ident);
            bool hasFound = false;
            string newRank = "";
            foreach(DZLOnlinePlayer newMedic: medics) {
                if(ident == newMedic.id) {
                    hasFound = true;
                    newRank = newMedic.rank;
                    break;
                }
            }
            player.UpdateMedic(hasFound, newRank);
        }
    }

    void UpdateArmy(ref array<DZLOnlinePlayer> army) {
        if(!army) return;

        foreach(string ident: playerIdentities) {
            DZLPlayer player = DZLDatabaseLayer.Get().GetPlayer(ident);
            bool hasFound = false;
            string newRank = "";
            foreach(DZLOnlinePlayer newArmy: army) {
                if(ident == newArmy.id) {
                    hasFound = true;
                    newRank = newArmy.rank;
                    break;
                }
            }
            player.UpdateArmy(hasFound, newRank);
        }
    }

    void UpdateCarKeys(PlayerIdentity player, CarScript car, ref array<DZLOnlinePlayer> players) {
        if(!players) return;

        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        if(!car.IsOwner(player)) return;

        car.UpdatePlayerAccessByDZLOnlinePlayer(players);
    }

    private bool Load() {
        if(GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName)) {
            JsonFileLoader<DZLPlayerIdentities>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, this);
            return true;
        }
        return false;
    }

    private bool Save() {
        if(GetGame().IsServer()) {
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER);
            DZLJsonFileHandler<DZLPlayerIdentities>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, this);
            return true;
        }
        return false;
    }

}
