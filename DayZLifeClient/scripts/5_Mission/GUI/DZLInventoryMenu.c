modded class Inventory : LayoutHolder
{
    TextWidget playerArrest;
    TextWidget moneyAtBank;
    TextWidget moneyAtPlayer;
    private Widget prisonPanel;

    void Inventory(LayoutHolder parent) {
        moneyAtPlayer = TextWidget.Cast(GetMainWidget().FindAnyWidget("DZLCash"));
        moneyAtBank = TextWidget.Cast(GetMainWidget().FindAnyWidget("DZLBank"));
        playerArrest = TextWidget.Cast(GetMainWidget().FindAnyWidget("playerArrest"));
        prisonPanel = TextWidget.Cast(GetMainWidget().FindAnyWidget("prisonPanel"));
    }

    override void OnShow() {
        super.OnShow();
		
		DZLPlayer dzlPlayer = DZLPlayerBaseHelper.GetPlayer().GetDZLPlayer();

         if (dzlPlayer) {
             moneyAtBank.SetText(dzlPlayer.GetBankMoney().ToString());
             moneyAtPlayer.SetText(dzlPlayer.GetMoney().ToString());
             playerArrest.SetText(dzlPlayer.arrestTimeInMinutes.ToString());
         }
     }
}
