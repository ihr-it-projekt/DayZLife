class DZLHarvestProgressBar: DZLBaseProgressBar {

    override void SetPlayer(PlayerBase _player) {
        super.SetPlayer(_player);

        DZLWorkZone zone = DZLConfig.Get().jobConfig.FindZone(player.GetPosition());

        if(!zone) {
            OnHide();
        }

        duration = zone.timeToHarvestPerItemInSeconds;
    }

    override void OnHide() {
        super.OnHide();
    }

    override void SendFinishEvent() {
        GetGame().RPCSingleParam(player, DZL_RPC.HARVEST, null, true);
    }
}
