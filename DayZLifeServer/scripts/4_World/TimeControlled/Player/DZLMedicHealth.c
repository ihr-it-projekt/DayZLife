class DZLMedicHealth
{
	static void CheckHealth(PlayerBase player, PlayerIdentity playerIdentity) {
	    bool showMedicHelpMenu = false;
        player.healByMedic = false;
        player.healByHospital = false;
        if (100 > player.GetHealth("GlobalHealth", "Blood")) {
            player.SetHealth("GlobalHealth", "Blood", 50);
            player.SetHealth("GlobalHealth", "Shock", 0);
            showMedicHelpMenu = true;
        }

        if (7 > player.GetHealth("GlobalHealth", "Health")) {
            player.SetHealth("GlobalHealth", "Health", 5);
            player.SetHealth("GlobalHealth", "Shock", 0);
            showMedicHelpMenu = true;
        }

        if (showMedicHelpMenu == true) {
            GetGame().RPCSingleParam(player, DAY_Z_LIFE_EVENT_MEDIC_SYNC_PLAYER, null, true, playerIdentity);
        }
	}

}
