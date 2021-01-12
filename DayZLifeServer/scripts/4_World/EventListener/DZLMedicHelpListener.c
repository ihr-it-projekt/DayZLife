class DZLMedicHelpListener
{
	DZLMedicConfig config;
	
    void DZLMedicHelpListener() {
		config = DZLConfig.Get().medicConfig;
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLMedicHelpListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_EVENT_MEDIC_KILL_PLAYER) {
           KillPlayer(PlayerBase.Cast(target));
           DeleteMedicRequest(sender);
        } else if (rpc_type == DAY_Z_LIFE_MEDIC_CALL) {
            DZLDatabaseLayer.Get().GetEmergencies().Add(sender.GetId());
            DZLSendMessage(sender, "#medics_was_called. #Heal_menu_can_be_open_with: 2 + LCTRL");
			DZLSendMedicMessage("#there_is_a_new_emergency");
		} else if (rpc_type == DAY_Z_LIFE_EVENT_HOSPITAL_HEAL_PLAYER) {
           HealByHospital(PlayerBase.Cast(target));
           DeleteMedicRequest(sender);
        } else if (rpc_type == DAY_Z_LIFE_GET_EMERGENCY_CALLS) {
            array<Man> players = new array<Man>;
            GetGame().GetPlayers(players);

			DZLEmergencies emergencies = DZLDatabaseLayer.Get().GetEmergencies();
			
            array<ref DZLOnlinePlayer> onlineEmergencies = new array<ref DZLOnlinePlayer>;
            foreach(Man _player: players) {
                string ident = _player.GetIdentity().GetId();
                
				if (emergencies.HasEmergency(ident)) {
					onlineEmergencies.Insert(new DZLOnlinePlayer(ident, _player.GetIdentity().GetName(), _player.GetPosition()));
				}
            }
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_GET_EMERGENCY_CALLS_RESPONSE, new Param1<ref array<ref DZLOnlinePlayer>>(onlineEmergencies), true, sender);
        }
    }

    private void DeleteMedicRequest(PlayerIdentity sender) {
		DZLDatabaseLayer.Get().GetEmergencies().Remove(sender.GetId());
	}

	private void HealByHospital(PlayerBase player) {
	    if (!player) return;
        player.healByMedic = false;
        player.healByHospital = true;
        player.noHealthDecrease = 10;

        DZLBaseSpawnPoint point = config.hospitalSpawnPoints.GetRandomElement();
        if (player.m_BleedingManagerServer) {
            player.m_BleedingManagerServer.RemoveAllSources();
        }

        DZLDatabaseLayer.Get().GetPlayer(player.GetIdentity().GetId()).AddMoneyToPlayerBank(config.priceHospitalHeal * -1);

        if (player.m_BrokenLegState == eBrokenLegs.BROKEN_LEGS) {
            ItemBase splint = ItemBase.Cast(player.GetInventory().CreateInInventory("Splint"));
            player.ApplySplint();
            player.m_BrokenLegState = eBrokenLegs.BROKEN_LEGS_SPLINT;
            ItemBase new_item = ItemBase.Cast(player.GetInventory().CreateInInventory("Splint_Applied"));
            MiscGameplayFunctions.TransferItemProperties(splint, new_item, true, false, true);
            GetGame().ObjectDelete(splint);
        }

        player.SetPosition(point.point);
        player.SetOrientation(point.orientation);
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_ALL_WAS_HEALED_RESPONSE, null, true, player.GetIdentity());
    }

    void KillPlayer(PlayerBase player) {
        if (!player) return;
        player.SetCanBeDestroyed(true);
        player.SetHealth(0);
    }
}
