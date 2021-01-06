class DZLMedicHelpListener
{
    void DZLMedicHelpListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLMedicHelpListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_EVENT_MEDIC_KILL_PLAYER) {
            autoptr Param1<PlayerBase>paramKill;
            if (ctx.Read(paramKill)){
                paramKill.param1.KillPlayer();
                DeleteMedicRequest(sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_MEDIC_CALL) {
            autoptr Param1<PlayerBase>paramCallMedic;
            if (ctx.Read(paramCallMedic)){
                DZLDatabaseLayer.Get().GetEmergencies().Add(sender.GetId());
                DZLSendMessage(sender, "#medics_was_called");
				DZLSendMedicMessage("#there_is_a_new_emergency");
			}
        } else if (rpc_type == DAY_Z_LIFE_EVENT_HOSPITAL_HEAL_PLAYER) {
            autoptr Param1<PlayerBase>paramHealHospital;
            if (ctx.Read(paramHealHospital)){
				PlayerBase player = paramHealHospital.param1;
                player.HealByHospital();
                DeleteMedicRequest(sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_GET_EMERGENCY_CALLS) {
            array<Man> players = new array<Man>;
            GetGame().GetPlayers(players);

			array<string> emergencyIds = DZLDatabaseLayer.Get().GetEmergencies().emergencies;
            array<ref DZLOnlinePlayer> onlineEmergencies = new array<ref DZLOnlinePlayer>;
            foreach(Man _player: players) {
                string ident = _player.GetIdentity().GetId();
                
				if (-1 == emergencyIds.Find(ident)) {
					onlineEmergencies.Insert(new DZLOnlinePlayer(ident, _player.GetIdentity().GetName(), _player.GetPosition()));
				}
            }
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_GET_EMERGENCY_CALLS_RESPONSE, new Param1<ref array<ref DZLOnlinePlayer>>(onlineEmergencies), true, sender);
        }
    }

    private void DeleteMedicRequest(PlayerIdentity sender) {
		DZLDatabaseLayer.Get().GetEmergencies().Remove(sender.GetId());
	}
}
