modded class Inventory : LayoutHolder
{
    TextWidget moneyAtBank;
    TextWidget moneyAtPlayer;
	private ref DZLUIItemCreator creator;
	
    void Inventory(LayoutHolder parent) {
        moneyAtPlayer = TextWidget.Cast(GetMainWidget().FindAnyWidget("DZLCash"));
        moneyAtBank = TextWidget.Cast(GetMainWidget().FindAnyWidget("DZLBank"));
    }

    override void OnShow() {
         super.OnShow();
         moneyAtBank.SetText(PlayerBaseHelper.GetPlayer().dzlPlayer.bank.ToString());
         moneyAtPlayer.SetText(PlayerBaseHelper.GetPlayer().dzlPlayer.money.ToString());
     }
}