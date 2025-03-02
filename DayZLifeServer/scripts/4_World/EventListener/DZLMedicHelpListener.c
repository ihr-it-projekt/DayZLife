class DZLMedicHelpListener: DZLBaseEventListener {

#ifdef TBRevivePlayerServer
    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.MEDIC_CALL) {
            DZLSendMessage(sender, "#medics_was_called.");
            DZLSendMedicMessage("#there_is_a_new_emergency");
            return;
        }
        if(rpc_type == DZL_RPC.GET_EMERGENCY_CALLS) {
            array<Man> players = new array<Man>;
            g_Game.GetPlayers(players);
			array<ref DZLOnlinePlayer> onlineEmergencies = new array<ref DZLOnlinePlayer>;
            
            foreach(Man _player: players) {
                PlayerBase player = PlayerBase.Cast(_player);
				if (!player || !player.tbrIsDead) continue;

                onlineEmergencies.Insert(new DZLOnlinePlayer(player.TBLibGetPlayerId(), player.TBLibGetPlayerName(), "", player.GetPosition()));
            }
            g_Game.RPCSingleParam(null, DZL_RPC.GET_EMERGENCY_CALLS_RESPONSE, new Param1<ref array<ref DZLOnlinePlayer>>(onlineEmergencies), true, sender);
        }
    }
#endif
}
