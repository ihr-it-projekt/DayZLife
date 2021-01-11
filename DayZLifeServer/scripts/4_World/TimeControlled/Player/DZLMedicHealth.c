class DZLMedicHealth
{
	static void CheckHealth(PlayerBase player, PlayerIdentity playerIdentity) {
	    bool showMedicHelpMenu = false;

        if (player.GetHealth("GlobalHealth", "Health") <= 0) {
            showMedicHelpMenu = true;
            player.SetHealth("GlobalHealth", "Health", 0);
            player.SetHealth("GlobalHealth", "Shock", 0);
        }

        if (player.GetHealth("GlobalHealth", "Blood") <= 0) {
            showMedicHelpMenu = true;
            player.SetHealth("GlobalHealth", "Blood", 0);
            player.SetHealth("GlobalHealth", "Shock", 0);
        }

        if (2 > player.GetHealth("GlobalHealth", "Shock")) {
            showMedicHelpMenu = true;
            player.SetHealth("GlobalHealth", "Shock", 0);
        }

        if (2 > player.GetHealth("GlobalHealth", "Blood")) {
            player.SetHealth("GlobalHealth", "Blood", 0);
            showMedicHelpMenu = true;
        }

        if (2 > player.GetHealth("GlobalHealth", "Health")) {
            player.SetHealth("GlobalHealth", "Health", 0);
            showMedicHelpMenu = true;
        }

        if (showMedicHelpMenu == true) {
            GetGame().RPCSingleParam(player, DAY_Z_LIFE_EVENT_MEDIC_SYNC_PLAYER, null, true, playerIdentity);
        }
	}

}
