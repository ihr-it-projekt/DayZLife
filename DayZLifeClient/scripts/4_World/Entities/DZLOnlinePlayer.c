class DZLOnlinePlayer: DZLNamePlayer {
    string id;
    vector position;
    string rank;

    void DZLOnlinePlayer(string id, string name, string rank, vector position = "0 0 0") {
        this.id = id;
        this.name = name;
        this.position = position;
        this.rank = rank;
    }
}
