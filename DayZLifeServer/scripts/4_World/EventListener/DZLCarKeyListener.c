class DZLCarKeyListener: DZLBaseEventListener {

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.GET_UPDATE_CAR_KEYS) {
            Param2<CarScript, ref array<DZLOnlinePlayer>> paramUpdateKeys;
            if(ctx.Read(paramUpdateKeys)) {

                DZLPlayerIdentities dzlPlayerIdentities = DZLDatabaseLayer.Get().GetPlayerIds();
                dzlPlayerIdentities.UpdateCarKeys(sender, paramUpdateKeys.param1, paramUpdateKeys.param2);
                DZLSendMessage(sender, "#update_car_key_list_successful");
            }
        } else if(rpc_type == DZL_RPC.GET_CAR_KEYS) {
            CarScript car = CarScript.Cast(target);

            array<ref DZLOnlinePlayer> keyOwner = new array<ref DZLOnlinePlayer>;
            array<string> keys = car.GetPlayerAccess();
            foreach(string playerId: keys) {
                DZLPlayer dPlayer = DZLDatabaseLayer.Get().GetPlayer(playerId);

                keyOwner.Insert(new DZLOnlinePlayer(dPlayer.dayZPlayerId, dPlayer.playerName, dPlayer.GetJobGrade()));
            }

            g_Game.RPCSingleParam(null, DZL_RPC.GET_CAR_KEYS_RESPONSE, new Param1<ref array<ref DZLOnlinePlayer>>(keyOwner), true, sender);
        } else if(rpc_type == DZL_RPC.GET_DAY_Z_LIFE_ALL_PLAYER_ONLINE_PLAYERS_FOR_ALL) {
            array<ref DZLOnlinePlayer> players = DZLDatabaseLayer.Get().GetPlayerIds().GetPlayerCollection(new array<string>);
            g_Game.RPCSingleParam(null, DZL_RPC.GET_DAY_Z_LIFE_ALL_PLAYER_ONLINE_PLAYERS_FOR_ALL_RESPONSE, new Param1<ref array<ref DZLOnlinePlayer>>(players), true, sender);
        } else if(rpc_type == DZL_RPC.CHANGE_CAR_OWNER) {
            Param2<string, CarScript> paramChangeOwner;
            if(ctx.Read(paramChangeOwner) && sender) {
                string receiverId = paramChangeOwner.param1;
                CarScript carToChange = paramChangeOwner.param2;
                DZLAdmin adminConfig = DZLConfig.Get().adminIds;
                if(!carToChange.IsOwner(sender) && !adminConfig.HasAccess(DAY_Z_LIFE_ACCESS_CARS, sender.GetId())) {
                    DZLSendMessage(sender, "#you_are_not_the_owner_can_not_change");
                    return;
                }

                DZLPlayer receiverPlayer = DZLDatabaseLayer.Get().GetPlayer(receiverId);
                if(!receiverPlayer) {
                    DZLSendMessage(sender, "#player_was_not_found");
                    return;
                }

                carToChange.ChangeOwner(receiverPlayer);
                DZLSendMessage(sender, "#owner_has_changed");
            }
        } else if(rpc_type == DZL_RPC.EVENT_CAR_RAID) {
            Param1<EntityAI> paramRaidCar;
            if(ctx.Read(paramRaidCar)) {
                DZLCarConfig carConfig = DZLConfig.Get().carConfig;
                int raidIndex = Math.RandomIntInclusive(1, carConfig.chanceToRaid);

                if(raidIndex == 1) {
                    CarScript raidedCar = CarScript.Cast(target);
                    raidedCar.isRaided = true;
                    raidedCar.SetSynchDirty();
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
