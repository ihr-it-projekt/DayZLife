class DZLCarKeyListener
{
	DZLCarConfig carConfig; 
	
    void DZLCarKeyListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
		carConfig = DZLConfig.Get().carConfig;
    }

    void ~DZLCarKeyListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_GET_UPDATE_CAR_KEYS) {
            autoptr Param2<CarScript, ref array<string>> paramUpdateKeys;
            if (ctx.Read(paramUpdateKeys)){

                DZLPlayerIdentities dzlPlayerIdentities = DZLDatabaseLayer.Get().GetPlayerIds();
                dzlPlayerIdentities.UpdateCarKeys(sender, paramUpdateKeys.param1, paramUpdateKeys.param2);
                DZLSendMessage(sender, "#update_car_key_list_successful");
            }
        } else if (rpc_type == DAY_Z_LIFE_GET_CAR_KEYS) {
            autoptr Param1<CarScript> paramGetKeys;
            if (ctx.Read(paramGetKeys)){
                CarScript car = paramGetKeys.param1;

				array<ref DZLOnlinePlayer> keyOwner = new array<ref DZLOnlinePlayer>;
				array<string> keys = car.GetPlayerAccess();
                foreach(string playerId: keys) {
					DZLPlayer dPlayer = DZLDatabaseLayer.Get().GetPlayer(playerId);
				
					keyOwner.Insert(new DZLOnlinePlayer(dPlayer.dayZPlayerId, dPlayer.playerName));
				}

                GetGame().RPCSingleParam(null, DAY_Z_LIFE_GET_CAR_KEYS_RESPONSE, new Param1<ref array<ref DZLOnlinePlayer>>(keyOwner), true, sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_GET_DAY_Z_LIFE_ALL_PLAYER_ONLINE_PLAYERS_FOR_ALL) {
            autoptr Param1<PlayerBase> paramGetAllPlayers;
            if (ctx.Read(paramGetAllPlayers)){
                array<ref DZLOnlinePlayer> players = DZLDatabaseLayer.Get().GetPlayerIds().GetPlayerCollection(new array<string>);
                GetGame().RPCSingleParam(paramGetAllPlayers.param1, DAY_Z_LIFE_GET_DAY_Z_LIFE_ALL_PLAYER_ONLINE_PLAYERS_FOR_ALL_RESPONSE, new Param1<ref array<ref DZLOnlinePlayer>>(players), true, sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_UPDATE_CAR_FROM_PLAYER_SIDE) {
            Param1<CarScript> carUpdateParam;
            if (ctx.Read(carUpdateParam)) {
                carUpdateParam.param1.SynchronizeValues(sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_EVENT_CAR_RAID) {
            Param3<PlayerBase, CarScript, EntityAI> paramRaidCar;
            if (ctx.Read(paramRaidCar)){
                int raidIndex = Math.RandomIntInclusive(1, carConfig.chanceToRaid);
				
				if (raidIndex == 1) {
					CarScript raidedCar = paramRaidCar.param2;
	               	raidedCar.isRaided = true;
	               	raidedCar.SynchronizeValues(null);
	               	paramRaidCar.param3.SetHealth(0);
	
	               	DZLSendMessage(sender, "#car_was_successful_raided");
					return;
				}

                DZLSendMessage(sender, "#car_raid_has_failed");
            }
        }
    }
}
