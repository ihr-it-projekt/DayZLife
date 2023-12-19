class DZLPlayerBaseHelper {
    static PlayerBase GetPlayer() {
        return PlayerBase.Cast(GetGame().GetPlayer());
    }
}