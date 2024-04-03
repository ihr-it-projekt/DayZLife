class DZLRaidListener: DZLBaseEventListener {

    private static ref map<BuildingBase, ref map<int, bool>> runningAlarms = new map<BuildingBase, ref map<int, bool>>;

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        switch(rpc_type) {
            case DZL_RPC.RAID_DOOR:
                RaidDoorFinished(sender, target, ctx);
                break;
            case DZL_RPC.RAID_DOOR_INTERRUPTED:
                RaidDoorInterrupted(sender, target, ctx);
                break;
            default:
                break;
        }
    }

    static void StartRaidDoor(PlayerBase raider, BuildingBase building, int doorIndex) {
        DZLMessageListener.SendMessage(raider, "", "#cop_message_house_alarm", DZLMessage.TYPE_COP, building.GetPosition(), false);
        DZLLogRaid(raider.GetIdentity().GetId(), "start raid", building.GetType(), building.GetPosition());
    }

    private void RaidDoorFinished(PlayerIdentity sender, Object target, ParamsReadContext ctx) {
        Param2<int, EntityAI> param;
        if(!ctx.Read(param)) return;

        BuildingBase building = BuildingBase.Cast(target);

        if(building.IsDoorLocked(param.param1))            building.UnlockDoor(param.param1);
        building.OpenDoor(param.param1);

        param.param2.SetHealth(0);
        DZLLogRaid(sender.GetId(), "raid done", building.GetType(), building.GetPosition());
    }

    private void RaidDoorInterrupted(PlayerIdentity player, Object target, ParamsReadContext ctx) {
        Param1<int> param;
        if(!ctx.Read(param)) return;

        BuildingBase building = BuildingBase.Cast(target);
        DZLLogRaid(player.GetId(), "raid interrupted", building.GetType(), building.GetPosition());
    }

}
