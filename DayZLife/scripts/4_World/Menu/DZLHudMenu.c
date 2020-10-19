class DZLHudMenu : UIScriptedMenu
{
	private ref DZLUIItemCreator creator;
    TextWidget moneyAtBank;
    TextWidget moneyAtPlayer;

    override Widget Init()
    {
        creator = new DZLUIItemCreator("DayZLife/layout/Banking/DZLCash.layout");
		
		layoutRoot = creator.GetLayoutRoot();
		moneyAtPlayer = creator.GetTextWidget("DZLCash");
		moneyAtBank = creator.GetTextWidget("DZLBank");

		return layoutRoot;
    }

    override void OnShow() {
		super.OnShow();
		moneyAtBank.SetText(PlayerBaseHelper.GetPlayer().dzlPlayer.bank.ToString());
		moneyAtPlayer.SetText(PlayerBaseHelper.GetPlayer().dzlPlayer.money.ToString());
	}
}