class DZLDoorRaidProgressBar: DZLBaseProgressBar
{
    private Building building;
    private int doorIndex;
	private EntityAI item;

    void SetBuilding(Building building, int doorIndex) {
        this.building = building;
        this.doorIndex = doorIndex;

		
        duration = 10;
        maxRange = 10;
        position = building.GetPosition();
    }
	
	void SetRaidItem(EntityAI item) {
		this.item = item;
	}
	
	override void SendFinishEvent() {
		
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_RAID_DOOR, new Param4<PlayerBase, Building, int, EntityAI>(player, building, doorIndex, item), true);
    }
}