class DZLAlmanacListener
{
    ref DZLConfig config;
	private ref DZLHouseFinder houseFinder;
	
    void DZLAlmanacListener() {
		config = DZLConfig.Get();
		houseFinder = new DZLHouseFinder;
		houseFinder.SetConfig(config);
		
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
        } else if (rpc_type == DAY_Z_LIFE_GET_ALL_PLAYERS) {
            SendAllPlayerList(sender);
        } else if (rpc_type == DAY_Z_LIFE_DELETE_PLAYER) {
            autoptr Param1<string> paramDeletePlayer;
            if (ctx.Read(paramDeletePlayer)){
				string identString = paramDeletePlayer.param1;
                if (DZLDatabaseLayer.Get().HasPlayer(identString)) {
                    DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(identString);
                    DZLPlayerHouse dzlPlayerHouse = DZLDatabaseLayer.Get().GetPlayerHouse(identString);
	
					DZLHouse house;
                    foreach(string fileNameHouse: dzlPlayerHouse.playerHouseCollection) {
                        house = DZLDatabaseLayer.Get().GetHouse(null, fileNameHouse);

                        array<ref DZLStorageTypeBought> storages = house.GetStorage();
                        if (storages && storages.Count() > 0) {
                            foreach(DZLStorageTypeBought storage: storages) {
                                if (!storage) continue;
                                houseFinder.objectFinder.DeleteContainerAt(storage.position, storage.position, storage.type);
                            }
                        }

                        house.RemoveOwner();

                        DZLDatabaseLayer.Get().GetBank().AddMoney(dzlPlayer.bank * -1);
                        DZLDatabaseLayer.Get().RemoveHouse(house.GetFileName());
                    }

                    foreach(string fileHouseAccess: dzlPlayerHouse.playerHouseKeyCollection) {
						house = DZLDatabaseLayer.Get().GetHouse(null, fileHouseAccess);
						if (house) house.RemovePlayerAccess(identString);
					}

                    DZLDatabaseLayer.Get().RemovePlayer(identString);
                    DZLDatabaseLayer.Get().RemovePlayerHouse(identString);
                    DZLDatabaseLayer.Get().GetPlayerIds().RemovePlayer(identString);
				}
				DZLSendMessage(sender, "#player_data_was_deleted");
				SendAllPlayerList(sender);
				
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

    void SendAllPlayerList(PlayerIdentity player) {
        if (!DZLConfig.Get().IsAdmin(player)) return;

        array<ref DZLPlayer> collection = new array<ref DZLPlayer>;
        DZLPlayerIdentities dzlPlayerIdentities = DZLDatabaseLayer.Get().GetPlayerIds();

		array<string> allPlayer = dzlPlayerIdentities.playerIdentities;
	    foreach(string ident: allPlayer) {
            DZLPlayer _player = DZLDatabaseLayer.Get().GetPlayer(ident);
            collection.Insert(_player);
		}

        GetGame().RPCSingleParam(null, DAY_Z_LIFE_GET_ALL_PLAYERS_RESPONSE, new Param1<ref array<ref DZLPlayer>>(collection), true, player);
    }
}
