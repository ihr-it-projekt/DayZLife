class DZLPlayerHouseListener
{
    ref DZLConfig config;

    void DZLPlayerHouseListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLPlayerHouseListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_GET_PLAYER_BUILDING) {
            autoptr Param1<PlayerBase> paramGetConfig;
            if (ctx.Read(paramGetConfig)){
                if (paramGetConfig.param1) {
                    GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_GET_PLAYER_BUILDING_RESPONSE, new Param1<ref DZLPlayerHouse>(new DZLPlayerHouse(sender)), true, sender);
                }
            }
        } else if (rpc_type == DAY_Z_LIFE_HOUSE_ACCESS_LISTS) {
			autoptr Param2<PlayerBase, Building> paramGetKeyLists;
            if (ctx.Read(paramGetKeyLists)){
                if (paramGetKeyLists.param1) {
                    SendUpdateList(paramGetKeyLists.param1, paramGetKeyLists.param2);
                }
            }
		} else if (rpc_type == DAY_Z_LIFE_HOUSE_ACCESS_LISTS_SAVE) {
			autoptr Param3<PlayerBase, Building, ref array<string>> paramSaveKeyLists;
            if (ctx.Read(paramSaveKeyLists)){
                DZLBuilding dzlBuilding = new DZLBuilding(paramSaveKeyLists.param2);
				PlayerBase playerOwner = paramSaveKeyLists.param1;
				array<string> playersAccess = paramSaveKeyLists.param3;
				
				if (!dzlBuilding.HasOwner() || !dzlBuilding.IsOwner(playerOwner)) return;
				
				dzlBuilding.UpdatePlayerAccess(playersAccess);
					
                SendUpdateList(playerOwner, paramSaveKeyLists.param2);
				DZLSendMessage(sender, "#keys_was_updated");
            }
		}
    }

    void SendUpdateList(PlayerBase player, Building building) {
    	DZLBuilding dzlBuilding = new DZLBuilding(building);

        if (!dzlBuilding.HasOwner() || !dzlBuilding.IsOwner(player)) return;
       
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        DZLPlayerIdentities dzlPlayerIdentities = new DZLPlayerIdentities;
		
		array <string> accessPlayer = dzlBuilding.GetPlayerAccess();
		
		string playerIdent =  player.GetIdentity().GetId();
		
		accessPlayer.Insert(playerIdent);
		
        array<ref DZLOnlinePlayer> noAccessIdents = dzlPlayerIdentities.GetPlayerCollection(accessPlayer);
		
		array<string> allPlayer = dzlPlayerIdentities.playerIdentities;
	    foreach(string ident: allPlayer) {
			if (dzlBuilding.HasPlayerAccess(ident) && ident != playerIdent) {
				DZLPlayer _player = new DZLPlayer(ident);
			    collection.Insert(new DZLOnlinePlayer(ident, _player.playerName));
			}
		}
		
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_HOUSE_ACCESS_LISTS_RESPONSE, new Param2<ref array<ref DZLOnlinePlayer>, ref array<ref DZLOnlinePlayer>>(collection, noAccessIdents), true, player.GetIdentity());
    }
}
