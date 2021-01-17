class DZLPlayerHouseListener
{
    void DZLPlayerHouseListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLPlayerHouseListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (!DZLLicenceCheck.Get().HasActiveLicence(sender)) return;
        if (rpc_type == DAY_Z_LIFE_GET_PLAYER_BUILDING) {
            GetGame().RPCSingleParam(target, DAY_Z_LIFE_GET_PLAYER_BUILDING_RESPONSE, new Param1<ref DZLPlayerHouse>(DZLDatabaseLayer.Get().GetPlayerHouse(sender.GetId())), true, sender);
        } else if (rpc_type == DAY_Z_LIFE_HOUSE_ACCESS_LISTS) {
			autoptr Param1<Building> paramGetKeyLists;
            if (ctx.Read(paramGetKeyLists)){
                PlayerBase playerGetPlayerBuilding = PlayerBase.Cast(target);
                if (playerGetPlayerBuilding) {
                    SendUpdateList(playerGetPlayerBuilding, paramGetKeyLists.param1);
                }
            }
		} else if (rpc_type == DAY_Z_LIFE_HOUSE_ACCESS_LISTS_SAVE) {
			autoptr Param2<Building, ref array<string>> paramSaveKeyLists;
            if (ctx.Read(paramSaveKeyLists)){
                Building buildingUpdateKey = paramSaveKeyLists.param1;
                DZLBuilding dzlBuilding = new DZLBuilding(buildingUpdateKey);
				PlayerBase playerOwner = PlayerBase.Cast(target);
				array<string> playersAccess = paramSaveKeyLists.param2;
				
				if (!dzlBuilding.HasOwner() || !dzlBuilding.IsOwner(playerOwner)) return;

				array<string> currentKeys = dzlBuilding.GetDZLHouse().GetPlayerAccess();
				
				array<string> playerMustUpdated = new array<string>;
				
				
				foreach(string playerIdWithNewAccess: playersAccess) {
					if (currentKeys.Find(playerIdWithNewAccess) == -1) {
                        DZLPlayerHouse playerHouseAccess = DZLDatabaseLayer.Get().GetPlayerHouse(playerIdWithNewAccess);

                        playerHouseAccess.AddKey(dzlBuilding.GetDZLHouse());
                        playerMustUpdated.Insert(playerIdWithNewAccess);
					}
				}

				foreach(string playerId: currentKeys) {
					if (playersAccess.Find(playerId) != -1) {
                        DZLPlayerHouse playerHouse = DZLDatabaseLayer.Get().GetPlayerHouse(playerId);

                        playerHouse.RemoveKey(dzlBuilding.GetDZLHouse());
                        playerMustUpdated.Insert(playerId);
					}
				}
				
				
				array<Man> onlinePlayers = new array<Man>;
				
				GetGame().GetPlayers(onlinePlayers);
				
				foreach(Man onlinePlayer: onlinePlayers) {
					PlayerIdentity playerIdent = onlinePlayer.GetIdentity();
					if (-1 != playerMustUpdated.Find(playerIdent.GetId())) {
						GetGame().RPCSingleParam(onlinePlayer, DAY_Z_LIFE_GET_PLAYER_BUILDING_RESPONSE, new Param1<ref DZLPlayerHouse>(DZLDatabaseLayer.Get().GetPlayerHouse(playerIdent.GetId())), true, playerIdent);
					}
				}
				
				dzlBuilding.UpdatePlayerAccess(playersAccess);
					
                SendUpdateList(playerOwner, buildingUpdateKey);
				DZLSendMessage(sender, "#keys_was_updated");
            }
		}
    }

    void SendUpdateList(PlayerBase player, Building building) {
    	DZLBuilding dzlBuilding = new DZLBuilding(building);

        if (!dzlBuilding.HasOwner() || !dzlBuilding.IsOwner(player)) return;
       
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        DZLPlayerIdentities dzlPlayerIdentities = DZLDatabaseLayer.Get().GetPlayerIds();
		
		array <string> accessPlayer = dzlBuilding.GetPlayerAccess();
		
		string playerIdent =  player.GetIdentity().GetId();
		
		accessPlayer.Insert(playerIdent);
		
        array<ref DZLOnlinePlayer> noAccessIdents = dzlPlayerIdentities.GetPlayerCollection(accessPlayer);
		
		array<string> allPlayer = dzlPlayerIdentities.playerIdentities;
	    foreach(string ident: allPlayer) {
	        DZLPlayer _player = DZLDatabaseLayer.Get().GetPlayer(ident);
			if (dzlBuilding.HasPlayerAccess(ident) && ident != playerIdent) {
			    collection.Insert(new DZLOnlinePlayer(ident, _player.playerName));
			}
		}
		
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_HOUSE_ACCESS_LISTS_RESPONSE, new Param2<ref array<ref DZLOnlinePlayer>, ref array<ref DZLOnlinePlayer>>(collection, noAccessIdents), true, player.GetIdentity());
    }
}
