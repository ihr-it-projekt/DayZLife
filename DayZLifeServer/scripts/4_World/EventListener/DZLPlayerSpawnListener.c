class DZLPlayerSpawnListener
{
    ref DZLConfig config;

    void DZLPlayerSpawnListener() {
        config = DZLConfig.Get();
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLPlayerSpawnListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_NEW_SPAWN) {
            autoptr Param3<string, PlayerBase, string> param;
            if (ctx.Read(param)){
                PlayerBase player = param.param2;
                player.RemoveAllItems();

                DZLJobSpawnPoints points = config.GetJobSpanwPointById(param.param3);
				
				DZLSpawnPoint point = points.FindSpawnById(param.param1);
				
				DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(player.GetIdentity().GetId());
				dzlPlayer.UpdateActiveJob(param.param3);
				
				if (point) {
					foreach(string item: point.items) {
						player.GetInventory().CreateInInventory(item);
					}
				}

				player.SetPosition(point.point);
				player.SetOrientation(point.orientation);
				
				GetGame().RPCSingleParam(player, DAY_Z_LIFE_NEW_SPAWN_RESPONSE, new Param1<string>(""), true, sender);
            }
        }
    }
}
