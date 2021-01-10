class DZLEscapedPlayer
{
    int arrestTime;
    string name;
    string arrestReason;
    DayZPlayer player;

    void DZLEscapedPlayer(DayZPlayer player, string arrestReason, int arrestTime) {
        this.name = player.GetIdentity().GetName();
        this.player = player;
        this.arrestTime = arrestTime;
		this.arrestReason = arrestReason;
    }
}
