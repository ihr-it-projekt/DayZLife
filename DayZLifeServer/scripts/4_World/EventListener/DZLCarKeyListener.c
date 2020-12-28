class DZLCarKeyListener
{
    void DZLCarKeyListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
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
				
                foreach(string playerId: car.GetPlayerAccess()) {
					DZLPlayer dPlayer = DZLDatabaseLayer.Get().GetPlayer(playerId);
				
					keyOwner.Insert(new DZLOnlinePlayer(dPlayer.dayZPlayerId, dPlayer.playerName));
				}

                GetGame().RPCSingleParam(null, DAY_Z_LIFE_GET_CAR_KEYS_RESPONSE, new Param1<ref array<ref DZLOnlinePlayer>>(keyOwner), true, sender);
            }
        }
    }
}
