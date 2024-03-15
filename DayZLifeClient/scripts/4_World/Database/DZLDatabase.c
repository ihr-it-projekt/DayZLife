class DZLDatabase {
    private ref map<string, ref DZLPlayer> dzlPlayers;
    private ref DZLPlayerIdentities dzlPlayerIdentities;
    private ref DZLBank bank;
    private ref DZLEmergencies emergencies;

    void DZLDatabase() {
        dzlPlayers = new map<string, ref DZLPlayer>;
    }

    void Init(DZLDatabaseLayer databaseLayer) {
        DZLPlayerIdentities dzlPlayerIdentities = databaseLayer.GetPlayerIds();

        array<string> allPlayer = dzlPlayerIdentities.playerIdentities;
        foreach(string ident: allPlayer) {
            DZLPlayer _player = databaseLayer.GetPlayerFromFiles(ident);
            dzlPlayers.Insert(ident, _player);
        }
    }

    DZLPlayer GetPlayer(string playerId) {
        if("" == playerId) return null;
        DZLPlayer player;
        if(!dzlPlayers.Find(playerId, player)) {
            player = new DZLPlayer(playerId, DZLConfig.Get().bankConfig.startCapital);
            dzlPlayers.Insert(playerId, player);
        }

        if(player.dayZPlayerId != playerId) {
            LogMessageDZL("there are inconsistent in your player database: Please check file:" + player.fileName);
            player = new DZLPlayer(playerId, DZLConfig.Get().bankConfig.startCapital);
            dzlPlayers.Insert(playerId, player);
        }

        return player;
    }

    void RemovePlayer(string playerId) {
        GetPlayer(playerId);

        DZLPlayer player;
        if(dzlPlayers.Find(playerId, player)) {
            dzlPlayers.Remove(playerId);
            DeleteFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + player.fileName);
        }
    }

    bool HasPlayer(string playerId) {
        DZLPlayer player;
        return dzlPlayers.Find(playerId, player);
    }
}
