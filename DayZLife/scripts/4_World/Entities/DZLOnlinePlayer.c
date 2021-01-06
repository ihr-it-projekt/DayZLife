class DZLOnlinePlayer
{
    string id;
    string name;
    vector position;

    void DZLOnlinePlayer(string id, string name, vector position = "0 0 0") {
        this.id = id;
        this.name = name;
        this.position = position;
    }
}
