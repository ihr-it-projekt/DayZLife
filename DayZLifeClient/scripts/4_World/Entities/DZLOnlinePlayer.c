class DZLOnlinePlayer: DZLNamePlayer {
    string id;
    vector position;
    string rank;

    void DZLOnlinePlayer(string _id, string _name, string _rank, vector _position = "0 0 0") {
        this.id = _id;
        this.name = _name;
        this.position = _position;
        this.rank = _rank;
    }
}
