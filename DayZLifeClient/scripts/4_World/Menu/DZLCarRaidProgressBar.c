class DZLCarRaidProgressBar: DZLBaseProgressBar {
    private CarScript car;
    private EntityAI item;

    override Widget Init() {
        return super.Init();
    }

    void SetCar(CarScript carIn) {
        this.car = carIn;

        duration = 999999999999999;
    }

    void SetRaidItem(EntityAI _item) {
        this.item = _item;
    }

    override void OnHide() {
        super.OnHide();
    }

    override void SendFinishEvent() {
        car.isRaided;
        g_Game.RPCSingleParam(car, DZL_RPC.EVENT_CAR_RAID, new Param1<EntityAI>(item), true);
    }
}
