modded class Inventory : LayoutHolder
{
    TextWidget playerArrest;
    TextWidget moneyAtBank;
    TextWidget moneyAtPlayer;
	private ref DZLUIItemCreator creator;
	
    void Inventory(LayoutHolder parent) {
        moneyAtPlayer = TextWidget.Cast(GetMainWidget().FindAnyWidget("DZLCash"));
        moneyAtBank = TextWidget.Cast(GetMainWidget().FindAnyWidget("DZLBank"));
        playerArrest = TextWidget.Cast(GetMainWidget().FindAnyWidget("playerArrest"));
    }

    override void OnShow() {
        super.OnShow();
		
		DZLPlayer dzlPlayer = PlayerBaseHelper.GetPlayer().dzlPlayer;

         if (dzlPlayer) {
             moneyAtBank.SetText(dzlPlayer.bank.ToString());
             moneyAtPlayer.SetText(dzlPlayer.money.ToString());
			 playerArrest.Show(dzlPlayer.IsPlayerInArrest());
             playerArrest.SetText(dzlPlayer.arrestTimeInMinutes.ToString());
         }
     }
}
