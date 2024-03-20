class DZLMedicHelpListener: DZLBaseEventListener {

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.EVENT_MEDIC_KILL_PLAYER) {
            DeleteMedicRequest(sender);
        } else if(rpc_type == DZL_RPC.MEDIC_CALL) {
            PlayerBase emergencyPlayer = PlayerBase.Cast(target);

            if(!emergencyPlayer) return;
#ifdef TBRevivePlayerServer
            TBREmergency emergency = new TBREmergency(emergencyPlayer);
            emergency.isMedic = true;
            TBREmergencies.Get().Add(emergency);
            DZLSendMessage(sender, "#medics_was_called.");
            DZLSendMedicMessage("#there_is_a_new_emergency");
#endif
        } else if(rpc_type == DZL_RPC.GET_EMERGENCY_CALLS) {
#ifdef TBRevivePlayerClient
            array<Man> players = new array<Man>;
            GetGame().GetPlayers(players);

            TBREmergencies emergencies = TBREmergencies.Get();

            array<ref DZLOnlinePlayer> onlineEmergencies = new array<ref DZLOnlinePlayer>;
            foreach(Man _player: players) {
                string ident = _player.GetIdentity().GetId();

                if(!emergencies.GetEmergency(ident)) continue;
                if(_player.GetHealth() > 1) {
                    emergencies.Remove(ident);
                    continue;
                }

                onlineEmergencies.Insert(new DZLOnlinePlayer(ident, _player.GetIdentity().GetName(), "", _player.GetPosition()));
            }
            GetGame().RPCSingleParam(null, DZL_RPC.GET_EMERGENCY_CALLS_RESPONSE, new Param1<ref array<ref DZLOnlinePlayer>>(onlineEmergencies), true, sender);
#endif
        }
    }

    private void DeleteMedicRequest(PlayerIdentity sender) {
#ifdef TBRevivePlayerClient
        TBREmergencies.Get().Remove(sender.GetId());
#endif
    }


}
