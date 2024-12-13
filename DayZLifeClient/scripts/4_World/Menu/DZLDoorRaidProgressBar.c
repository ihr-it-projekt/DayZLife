class DZLDoorRaidProgressBar: DZLBaseProgressBar {
    private BuildingBase building;
    private int doorIndex;
    private ItemBase item;
    private DZLJobHouseDefinition definition;

    void SetBuilding(BuildingBase _building, int _doorIndex, DZLJobHouseDefinition _definition) {
        this.building = _building;
        this.doorIndex = _doorIndex;
        this.definition = _definition;

        if(!definition) {
            OnHide();
            SendInterruptEvent();
            return;
        }

        duration = definition.raidTimeInSeconds;
    }

    override void CheckDuration() {
        super.CheckDuration();

        item = player.GetItemInHands();

        if(!item || -1 == definition.raidTools.Find(item.GetType())) {
            OnHide();
            SendInterruptEvent();
        }
    }

    override void SendFinishEvent() {
        g_Game.RPCSingleParam(building, DZL_RPC.RAID_DOOR, new Param2<int, ItemBase>(doorIndex, item), true);
    }

    override void SendInterruptEvent() {
        g_Game.RPCSingleParam(building, DZL_RPC.RAID_DOOR_INTERRUPTED, new Param1<int>(doorIndex), true);
    }
}
