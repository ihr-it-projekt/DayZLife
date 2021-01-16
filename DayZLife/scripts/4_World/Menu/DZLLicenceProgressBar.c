class DZLLicenceProgressBar: DZLBaseProgressBar
{
    private DZLLicence licence;

    override void OnShow() {
        super.OnShow();
        licence = player.GetLicenceByPosition();
        duration = licence.durationForCrafting;
        maxRange = licence.range;
        position = licence.position;
    }
	
    override void SendFinishEvent() {
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_BUY_LICENCE_USE, new Param1<string>(licence.id), true);
    }
}
