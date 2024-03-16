modded class DZLPlayerIdentities {

    void DZLPlayerIdentities() {
        Init(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER, "DZLPlayerIdentities");
        Load();
    }

    override void AddPlayer(string playerId) {
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

    array<ref DZLOnlinePlayer> GetJobPlayerCollection(string jobName) {
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        foreach(string ident: playerIdentities) {
            DZLPlayer player = DZLDatabaseLayer.Get().GetPlayer(ident);

            if(player.CanUseJob(jobName)) {
                collection.Insert(new DZLOnlinePlayer(ident, player.playerName, player.GetLastJobRank(jobName)));
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

    void UpdateJob(string job, ref array<DZLOnlinePlayer> players) {
        if(!players) return;

        foreach(string ident: playerIdentities) {
            DZLPlayer player = DZLDatabaseLayer.Get().GetPlayer(ident);
            bool hasFound = false;
            string newRank = "";
            foreach(DZLOnlinePlayer dzlPlayer: players) {
                if(ident == dzlPlayer.id) {
                    hasFound = true;
                    newRank = dzlPlayer.rank;
                    break;
                }
            }

            player.UpdateJob(job, hasFound, newRank);
        }
    }

    void UpdateCarKeys(PlayerIdentity player, CarScript car, ref array<DZLOnlinePlayer> players) {
        if(!players) return;

        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        if(!car.IsOwner(player)) return;

        car.UpdatePlayerAccessByDZLOnlinePlayer(players);
    }

    override protected bool Read(FileSerializer ctx) {
        playerIdentities = new array<string>;
        int count = 0;
        ctx.Read(count);

        for(int i = 0; i < count; i++) {
            string value = "";
            ctx.Read(value);
            playerIdentities.Insert(value);
        }

        return true;
    }

    override protected void Write(FileSerializer ctx) {
        ctx.Write(playerIdentities.Count());
        foreach(string value : playerIdentities) {
            ctx.Write(value);
        }
    }
}
