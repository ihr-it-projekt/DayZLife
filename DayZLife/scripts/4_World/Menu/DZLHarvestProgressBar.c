class DZLHarvestProgressBar: DZLBaseProgressBar
{

    override void SetPlayer(PlayerBase player) {
        super.SetPlayer(player);

        DZLWorkZone zone = player.GetConfig().jobConfig.FindZone(player.GetPosition());
		
		if (!zone)  {
			OnHide();
		}

        duration = zone.timeToHarvestPerItemInSeconds;
    }

	override void OnHide() {
		super.OnHide();
	}
	
	override void SendFinishEvent() {
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_HARVEST, null, true);
    }
}
