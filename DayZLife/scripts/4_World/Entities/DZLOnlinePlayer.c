class DZLOnlinePlayer
{
    string id;
    string name;
    vector position;
	string rang;

    void DZLOnlinePlayer(string id, string name, string rang, vector position = "0 0 0") {
        this.id = id;
        this.name = name;
        this.position = position;
		this.rang = rang;
    }
}
