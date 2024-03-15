class DZLEscapedPlayer {
    int arrestTime;
    string name;
    string arrestReason;
    DayZPlayer player;

    void DZLEscapedPlayer(PlayerBase _player) {
        this.name = _player.GetIdentity().GetName();
        this.player = _player;
        this.arrestTime = _player.GetDZLPlayer().arrestTimeInMinutes;
        this.arrestReason = _player.GetDZLPlayer().arrestReason;
    }
}
