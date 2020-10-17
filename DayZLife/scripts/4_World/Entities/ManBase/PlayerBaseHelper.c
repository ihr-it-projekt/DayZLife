class PlayerBaseHelper {
    static PlayerBase GetPlayer() {
		return PlayerBase.Cast(GetGame().GetPlayer());
	}

}