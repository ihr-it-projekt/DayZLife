class DZLPlayerHouseListener
{
    void DZLPlayerHouseListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLPlayerHouseListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
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
			autoptr Param2<Building, ref array<DZLOnlinePlayer>> paramSaveKeyLists;
            if (ctx.Read(paramSaveKeyLists)){
                Building buildingUpdateKey = paramSaveKeyLists.param1;
                DZLBuilding dzlBuilding = new DZLBuilding(buildingUpdateKey);
				PlayerBase playerOwner = PlayerBase.Cast(target);
				array<DZLOnlinePlayer> playersAccess = paramSaveKeyLists.param2;
				
				if (!dzlBuilding.HasOwner() || !dzlBuilding.IsOwner(playerOwner)) return;

                array<string> playerMustUpdated = new array<string>;

				array<string> currentKeys = dzlBuilding.GetDZLHouse().GetPlayerAccess();
				foreach(string playerId: currentKeys) {
                    DZLPlayerHouse playerHouse = DZLDatabaseLayer.Get().GetPlayerHouse(playerId);

                    playerHouse.RemoveKey(dzlBuilding.GetDZLHouse());
                    playerMustUpdated.Insert(playerId);
                }
				
				foreach(DZLOnlinePlayer playerIdWithNewAccess: playersAccess) {
                    DZLPlayerHouse playerHouseAccess = DZLDatabaseLayer.Get().GetPlayerHouse(playerIdWithNewAccess.id);

                    playerHouseAccess.AddKey(dzlBuilding.GetDZLHouse());
                    playerMustUpdated.Insert(playerIdWithNewAccess.id);
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
		} else if (rpc_type == DAY_Z_LIFE_OPEN_GET_BUILDING_INVENTORY_DATA) {
		    autoptr Param2<string, vector> paramInventory;
            if (ctx.Read(paramInventory)){
                string fileName = DZLHouse.GetFileNameByPosition(paramInventory.param2);
                DZLHouse houseInventory = DZLDatabaseLayer.Get().GetHouse(null, fileName);
                if (!houseInventory || !houseInventory.HasInventory()) return;

                DZLHouseInventory inventoryGet = DZLDatabaseLayer.Get().GetHouseInventory(paramInventory.param1, paramInventory.param2);

				GetGame().RPCSingleParam(null, DAY_Z_LIFE_OPEN_GET_BUILDING_INVENTORY_DATA_RESPONSE, new Param1<ref DZLHouseInventory>(inventoryGet), true, sender);
            }
		} else if (rpc_type == DAY_Z_LIFE_HOUSE_STORE_ITEMS) {
		    autoptr Param4<string, vector, ref array<string>, ref array<EntityAI>> paramStoreInventory;
            if (ctx.Read(paramStoreInventory)){
                array<string> storeOutItems = paramStoreInventory.param3;
                array<EntityAI> storeInItems = paramStoreInventory.param4;
                PlayerBase playerStore = PlayerBase.Cast(target);

                if (!playerStore) return;
                DZLHouse houseStore = DZLDatabaseLayer.Get().GetHouse(null, DZLHouse.GetFileNameByPosition(paramStoreInventory.param2));

                if (!houseStore || !houseStore.HasInventory()) return;
                DZLHouseInventory inventory = DZLDatabaseLayer.Get().GetHouseInventory(paramStoreInventory.param1, paramStoreInventory.param2);

                if (!inventory) return;

                foreach(string itemId: storeOutItems) {
                    DZLStoreItem storeOutItem = inventory.GetById(itemId);
                    if (!storeOutItem) continue;

                    DZLSpawnHelper.Add(playerStore, storeOutItem);
                    inventory.Remove(storeOutItem);
                }

                if (storeInItems.Count() > 0 && inventory.CanAddToStore(storeInItems)) {
                    inventory.AddToStore(storeInItems);
                }

                GetGame().RPCSingleParam(null, DAY_Z_LIFE_OPEN_GET_BUILDING_INVENTORY_DATA_RESPONSE, new Param1<ref DZLHouseInventory>(inventory), true, sender);
            }
		}
    }

    void SendUpdateList(PlayerBase player, Building building) {
    	DZLBuilding dzlBuilding = new DZLBuilding(building);

        if (!dzlBuilding.HasOwner() || !dzlBuilding.IsOwner(player)) return;
       
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        DZLPlayerIdentities dzlPlayerIdentities = DZLDatabaseLayer.Get().GetPlayerIds();
		
		array <string> accessPlayer = dzlBuilding.GetPlayerAccess();
		
		string playerIdent =  player.GetPlayerId();
		
		accessPlayer.Insert(playerIdent);
		
        array<ref DZLOnlinePlayer> noAccessIdents = dzlPlayerIdentities.GetPlayerCollection(accessPlayer);
		
		array<string> allPlayer = dzlPlayerIdentities.playerIdentities;
	    foreach(string ident: allPlayer) {
	        DZLPlayer _player = DZLDatabaseLayer.Get().GetPlayer(ident);
			if (dzlBuilding.HasPlayerAccess(ident) && ident != playerIdent) {
			    collection.Insert(new DZLOnlinePlayer(ident, _player.playerName, ""));
			}
		}
		
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_HOUSE_ACCESS_LISTS_RESPONSE, new Param2<ref array<ref DZLOnlinePlayer>, ref array<ref DZLOnlinePlayer>>(collection, noAccessIdents), true, player.GetIdentity());
    }
}
