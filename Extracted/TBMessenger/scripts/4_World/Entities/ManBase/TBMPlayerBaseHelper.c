class TBMPlayerBaseHelper {
    static PlayerBase GetPlayer() {
		return PlayerBase.Cast(GetGame().GetPlayer());
	}
}