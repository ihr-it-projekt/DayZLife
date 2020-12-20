class DZLEscapedPlayer
{
    int arrestTime;
    string name;
    DayZPlayer player;

    void DZLEscapedPlayer(DayZPlayer player, int arrestTime) {
        this.name = player.GetIdentity().GetName();
        this.player = player;
        this.arrestTime = arrestTime;
    }
}
