class DZLAlmanacListener
{
    ref DZLConfig config;

    void DZLAlmanacListener() {
		config = DZLConfig.Get();
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLAlmanacListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_ALL_PLAYER_ONLINE_PLAYERS) {
            autoptr Param1<PlayerBase> param;
            if (ctx.Read(param)){
				SendUpdateList(param.param1);
            }
        } else if (rpc_type == DAY_Z_LIFE_ALL_PLAYER_UPDATE_COP_PLAYERS) {
            autoptr Param2<PlayerBase, ref array<string>> paramUpdateCops;
            if (ctx.Read(paramUpdateCops)){
				PlayerIdentity ident = paramUpdateCops.param1.GetIdentity();
				
                if (!config.IsAdmin(ident)) return;

                DZLPlayerIdentities dzlPlayerIdentities = DZLDatabaseLayer.Get().GetPlayerIds();
                dzlPlayerIdentities.UpdateCops(paramUpdateCops.param2);
				DZLSendMessage(ident, "#update_cop_list_successful");
            }
        }
    }

    void SendUpdateList(PlayerBase player) {
        if (!config.IsAdmin(player.GetIdentity())) return;

        array<Man> _players = new array<Man>;
        GetGame().GetPlayers(_players);
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        DZLPlayerIdentities dzlPlayerIdentities = DZLDatabaseLayer.Get().GetPlayerIds();
        array<ref DZLOnlinePlayer> copIdents = dzlPlayerIdentities.GetCopPlayerCollection();

        if (_players) {
            foreach(Man _player: _players) {
				string ident = _player.GetIdentity().GetId();
               	DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(ident);
				
				if (!dzlPlayer.isCop) {
					collection.Insert(new DZLOnlinePlayer(ident, _player.GetIdentity().GetName()));
				}
                
            }
        }

		
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_ALL_PLAYER_ONLINE_PLAYERS_RESPONSE, new Param2<ref array<ref DZLOnlinePlayer>, ref array<ref DZLOnlinePlayer>>(collection, copIdents), true, player.GetIdentity());
    }
}
