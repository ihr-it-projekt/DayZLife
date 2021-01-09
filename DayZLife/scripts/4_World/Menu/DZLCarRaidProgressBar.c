class DZLCarRaidProgressBar: DZLBaseProgressBar
{
    private CarScript car;
	private EntityAI item;

	override Widget Init() {
        return super.Init();
    }

    void SetCar(CarScript car) {
        this.car = car;

        duration = 999999999999999;
        maxRange = 10;
        position = car.GetPosition();
    }
	
	void SetRaidItem(EntityAI item) {
		this.item = item;
	}

	override void OnHide() {
	    super.OnHide();
	}
	
	override void SendFinishEvent() {
	    car.isRaided;
	    DZLLogRaid(player.GetIdentity().GetId(), "raid car", car.GetType(), car.GetPosition());
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_EVENT_CAR_RAID, new Param3<PlayerBase, CarScript, EntityAI>(player, car, item), true);
    }
}
