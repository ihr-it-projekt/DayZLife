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

    array<ref DZLOnlinePlayer> GetCopPlayerCollection() {
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        foreach(string ident: playerIdentities) {
            DZLPlayer player = new DZLPlayer(ident);

            if (player.isCop) {
                collection.Insert(new DZLOnlinePlayer(ident, player.playerName));
            }
        }

        return collection;
    }

    void UpdateCops(array<string> cops) {
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        foreach(string ident: playerIdentities) {
            DZLPlayer player = new DZLPlayer(ident);
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

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName)) {
            JsonFileLoader<DZLPlayerIdentities>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER);
            DZLJsonFileHandler<DZLPlayerIdentities>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, this);
        }
    }

}
