class DZLPlayerBaseHelper {
    static PlayerBase GetPlayer() {
        return PlayerBase.Cast(g_Game.GetPlayer());
    }
}