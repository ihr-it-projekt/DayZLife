class DZLEscapedPlayer {
    int arrestTime;
    string name;
    string arrestReason;
    DayZPlayer player;

    void DZLEscapedPlayer(PlayerBase player) {
        this.name = player.GetIdentity().GetName();
        this.player = player;
        this.arrestTime = player.GetDZLPlayer().arrestTimeInMinutes;
        this.arrestReason = player.GetDZLPlayer().arrestReason;
    }
}
