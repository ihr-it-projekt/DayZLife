class DZLPlayerSpawnListener: DZLBaseEventListener {

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.NEW_SPAWN) {
            Param2<string, string> param;
            if(ctx.Read(param) && param.param1 && param.param2) {
                PlayerBase player = PlayerBase.Cast(target);
                if(!player) return;

                DZLJobSpawnPoints points = DZLConfig.Get().GetJobSpawnPointsByJobId(param.param2);
                DZLSpawnPoint point = points.FindSpawnById(param.param1);

                if(point) {
                    DZLPlayer dzlPlayer = player.GetDZLPlayer();
                    dzlPlayer.UpdateActiveJob(param.param2);

                    player.RemoveAllItems();
                    player.GetDZLPlayer().LoosPlayerInventoryMoney();
                    foreach(string item: point.items) {
                        player.GetInventory().CreateInInventory(item);
                    }

                    player.SetPosition(point.point);
                    player.SetOrientation(point.orientation);
                } else Error("No spawn point found for job: " + param.param2 + " and point id: " + param.param1);

                player.SetIsSpawned();

                dzlPlayer.UpdateDZLPlayerAtPlayer();
                g_Game.RPCSingleParam(null, DZL_RPC.NEW_SPAWN_RESPONSE, null, true, sender);
            }
        }
    }
}
