class DZLPlayerSpawnListener: DZLBaseEventListener {

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.NEW_SPAWN) {
            autoptr Param2<string, string> param;
            if(ctx.Read(param) && param.param1 && param.param2) {
                PlayerBase player = PlayerBase.Cast(target);
                if(!player) return;

                player.RemoveAllItems();
                player.GetDZLPlayer().LoosPlayerInventoryMoney();

                DZLJobSpawnPoints points = DZLConfig.Get().GetJobSpawnPointsByJobId(param.param2);
                DZLSpawnPoint point = points.FindSpawnById(param.param1);

                DZLPlayer dzlPlayer = player.GetDZLPlayer();
                dzlPlayer.UpdateActiveJob(param.param2);

                if(point) {
                    foreach(string item: point.items) {
                        player.GetInventory().CreateInInventory(item);
                    }
                }

                player.SetPosition(point.point);
                player.SetOrientation(point.orientation);
                player.SetIsSpawned();

                dzlPlayer.UpdateDZLPlayerAtPlayer();
                GetGame().RPCSingleParam(null, DZL_RPC.NEW_SPAWN_RESPONSE, null, true, sender);
            }
        }
    }
}
