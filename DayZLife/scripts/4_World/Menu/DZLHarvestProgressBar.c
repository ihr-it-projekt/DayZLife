class DZLHarvestProgressBar: DZLBaseProgressBar
{

    override void SetPlayer(PlayerBase player) {
        super.SetPlayer(player);

        DZLWorkZone zone = player.config.jobConfig.FindZone(player.GetPosition());
		
		if (!zone)  {
			OnHide();
		}

        duration = zone.timeToHarvestPerItemInSeconds;
        maxRange = zone.range;
        position = zone.position;
    }

	override void OnHide() {
		super.OnHide();
	}
	
	override void SendFinishEvent() {
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_HARVEST, new Param1<PlayerBase>(player), true);
    }
}
