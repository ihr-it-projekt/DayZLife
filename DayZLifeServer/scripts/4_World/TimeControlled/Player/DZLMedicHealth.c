class DZLMedicHealth
{
	static void CheckHealth(PlayerBase player, PlayerIdentity playerIdentity) {
	    bool showMedicHelpMenu = false;

        if (player.noHealthDecrease > 0) {
            if (player.healByHospital) {
                player.SetHealth01("GlobalHealth", "Health", 1);
                player.SetHealth01("GlobalHealth", "Blood", 1);
                player.SetHealth01("GlobalHealth", "Shock", 1);
            } else if (player.healByMedic) {
                player.SetHealth01("GlobalHealth", "Health", 0.5);
                player.SetHealth01("GlobalHealth", "Blood", 0.5);
                player.SetHealth01("GlobalHealth", "Shock", 0.5);
            }
            --player.noHealthDecrease;
        } else {
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

}
