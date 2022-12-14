class TBMOnlinePlayer
{
    string id;
    vector position;
	string name;

    void TBMOnlinePlayer(string id, string name, vector position = "0 0 0") {
        this.id = id;
        this.name = name;
        this.position = position;
    }
}
