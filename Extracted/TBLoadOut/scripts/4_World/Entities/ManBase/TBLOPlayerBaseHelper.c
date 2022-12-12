class TBLOPlayerBaseHelper {
    static PlayerBase GetPlayer() {
		return PlayerBase.Cast(GetGame().GetPlayer());
	}
}