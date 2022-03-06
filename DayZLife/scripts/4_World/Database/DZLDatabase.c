class DZLDatabase: Container_Base
{
    static vector POSITION = "10 0 10";
    private ref map<string, ref DZLHouse> dzlHouses;
    private ref map<string, ref DZLPlayer> dzlPlayers;
    private ref map<string, ref DZLPlayerHouse> dzlPlayerHouses;
    private ref DZLPlayerIdentities dzlPlayerIdentities;
    private ref DZLLockedHouses dzlLockedHouses;
    private ref DZLBank bank;
    private ref DZLEmergencies emergencies;

    override void EEInit() {
        super.EEInit();
        dzlPlayers = new map<string, ref DZLPlayer>;
        array<ref DZLPlayer> collection = new array<ref DZLPlayer>;
        DZLDatabaseLayer.Get().SetDatabase(this);

        DZLPlayerIdentities dzlPlayerIdentities = DZLDatabaseLayer.Get().GetPlayerIds();
        array<string> allPlayer = dzlPlayerIdentities.playerIdentities;
        foreach(string ident: allPlayer) {
            DZLPlayer _player = DZLDatabaseLayer.Get().GetPlayerFromFiles(ident);
            dzlPlayers.Insert(ident, _player);
        }

        SetAllowDamage(false);
    }

	DZLPlayer GetPlayer(string playerId) {
        DZLPlayer player;
        if (!dzlPlayers.Find(playerId, player)) {
            player = new DZLPlayer(playerId, DZLConfig.Get().bankConfig.startCapital);
            dzlPlayers.Insert(playerId, player);
        }

        if (player.dayZPlayerId != playerId) {
            LogMessageDZL("there are inconsistent in your player database: Please check file:" + player.fileName);
            player = new DZLPlayer(playerId, DZLConfig.Get().bankConfig.startCapital);
            dzlPlayers.Insert(playerId, player);
        }

        return player;
    }

    void RemovePlayer(string playerId) {
        GetPlayer(playerId);

        DZLPlayer player;
        if (dzlPlayers.Find(playerId, player)) {
            dzlPlayers.Remove(playerId);
            DeleteFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + player.fileName);
        }
    }

    bool HasPlayer(string playerId) {
        DZLPlayer player;
        return dzlPlayers.Find(playerId, player);
    }
}
