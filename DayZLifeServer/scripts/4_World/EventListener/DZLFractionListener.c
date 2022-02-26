class DZLFractionListener
{
	DZLFractionConfig config;

    void DZLFractionListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
		carConfig = DZLConfig.Get().carConfig;
    }

    void ~DZLFractionListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_GET_UPDATE_CAR_KEYS) {
            autoptr Param2<CarScript, ref array<DZLOnlinePlayer>> paramUpdateKeys;
            if (ctx.Read(paramUpdateKeys)){

                DZLPlayerIdentities dzlPlayerIdentities = DZLDatabaseLayer.Get().GetPlayerIds();
                dzlPlayerIdentities.UpdateCarKeys(sender, paramUpdateKeys.param1, paramUpdateKeys.param2);
                DZLSendMessage(sender, "#update_car_key_list_successful");
            }
        } else if (rpc_type == DAY_Z_LIFE_GET_CAR_KEYS) {
            CarScript car = CarScript.Cast(target);

            array<ref DZLOnlinePlayer> keyOwner = new array<ref DZLOnlinePlayer>;
            array<string> keys = car.GetPlayerAccess();
            foreach(string playerId: keys) {
                DZLPlayer dPlayer = DZLDatabaseLayer.Get().GetPlayer(playerId);

                keyOwner.Insert(new DZLOnlinePlayer(dPlayer.dayZPlayerId, dPlayer.playerName, dPlayer.GetJobGrade()));
            }

            GetGame().RPCSingleParam(null, DAY_Z_LIFE_GET_CAR_KEYS_RESPONSE, new Param1<ref array<ref DZLOnlinePlayer>>(keyOwner), true, sender);
        } else if (rpc_type == DAY_Z_LIFE_GET_DAY_Z_LIFE_ALL_PLAYER_ONLINE_PLAYERS_FOR_ALL) {
            array<ref DZLOnlinePlayer> players = DZLDatabaseLayer.Get().GetPlayerIds().GetPlayerCollection(new array<string>);
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_GET_DAY_Z_LIFE_ALL_PLAYER_ONLINE_PLAYERS_FOR_ALL_RESPONSE, new Param1<ref array<ref DZLOnlinePlayer>>(players), true, sender);
        } else if (rpc_type == DAY_Z_LIFE_UPDATE_CAR_FROM_PLAYER_SIDE) {
            CarScript.Cast(target).SynchronizeValues(sender);
        } else if (rpc_type == DAY_Z_LIFE_CHANGE_CAR_OWNER) {
            autoptr Param2<string, CarScript> paramChangeOwner;
            if (ctx.Read(paramChangeOwner) && sender){
                string receiverId = paramChangeOwner.param1;
                CarScript carToChange = paramChangeOwner.param2;
                if (!carToChange.IsOwner(sender)) {
                    DZLSendMessage(sender, "#you_are_not_the_owner_can_not_change");
                    return;
                }

                DZLPlayer receiverPlayer = DZLDatabaseLayer.Get().GetPlayer(receiverId);
                if (!receiverPlayer) {
                    DZLSendMessage(sender, "#player_was_not_found");
                    return;
                }

                carToChange.ChangeOwner(receiverPlayer);
                DZLSendMessage(sender, "#owner_has_changed");
           }
        } else if (rpc_type == DAY_Z_LIFE_EVENT_CAR_RAID) {
            Param1<EntityAI> paramRaidCar;
            if (ctx.Read(paramRaidCar)){
                int raidIndex = Math.RandomIntInclusive(1, carConfig.chanceToRaid);
				
				if (raidIndex == 1) {
					CarScript raidedCar = CarScript.Cast(target);
	               	raidedCar.isRaided = true;
	               	raidedCar.SynchronizeValues(null);
	               	paramRaidCar.param1.SetHealth(0);

	               	DZLSendMessage(sender, "#car_was_successful_raided");
	               	DZLLogRaid(sender.GetId(), "raid car", raidedCar.GetType(), raidedCar.GetPosition());
					return;
				}

                DZLSendMessage(sender, "#car_raid_has_failed");
                paramRaidCar.param1.SetHealth(0);
            }
        }
    }
}
