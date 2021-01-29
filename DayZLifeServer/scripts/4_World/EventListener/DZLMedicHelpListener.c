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
            DZLPlayer dzlPlayerKill = PlayerBase.Cast(target).GetDZLPlayer();
			dzlPlayerKill.SetDieState();
            DeleteMedicRequest(sender);
        } else if (rpc_type == DAY_Z_LIFE_MEDIC_CALL) {
            DZLDatabaseLayer.Get().GetEmergencies().Add(sender.GetId());
            DZLSendMessage(sender, "#medics_was_called. #Heal_menu_can_be_open_with: 2 + LCTRL");
			DZLSendMedicMessage("#there_is_a_new_emergency");
		} else if (rpc_type == DAY_Z_LIFE_EVENT_HOSPITAL_HEAL_PLAYER) {
           HealByHospital(PlayerBase.Cast(target), sender);
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

	private void HealByHospital(PlayerBase player, PlayerIdentity sender) {
	    if (!player) return;
        DZLPlayer dzlPlayer = player.GetDZLPlayer();
        dzlPlayer.AddMoneyToPlayerBank(config.priceHospitalHeal * -1);
        dzlPlayer.SetWillHealByHospital();
        dzlPlayer.SaveItems(player);
        GetGame().RPCSingleParam(null, DAY_Z_LIFE_ALL_WAS_HEALED_RESPONSE, null, true, sender);
    }
}
