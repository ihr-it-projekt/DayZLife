class DZLLicenceProgressBar: DZLBaseProgressBar {
    private DZLCraftLicence licence;

    override void OnShow() {
        super.OnShow();
        licence = player.GetLicenceByPosition();
        duration = licence.durationForCrafting;
        position = licence.position;
    }

    override void SendFinishEvent() {
        g_Game.RPCSingleParam(player, DZL_RPC.BUY_LICENCE_USE, new Param1<string>(licence.GetId()), true);
    }
}
