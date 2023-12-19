modded class Inventory {
    TextWidget playerArrest;
    TextWidget moneyAtBank;
    TextWidget moneyAtPlayer;
    private Widget dzlHud;

    void Inventory(LayoutHolder parent) {
        dzlHud = GetGame().GetWorkspace().CreateWidgets("DayZLifeClient/layout/Banking/hud.layout", GetMainWidget());
        moneyAtPlayer = TextWidget.Cast(dzlHud.FindAnyWidget("DZLCash"));
        moneyAtBank = TextWidget.Cast(dzlHud.FindAnyWidget("DZLBank"));
        playerArrest = TextWidget.Cast(dzlHud.FindAnyWidget("playerArrest"));
    }

    override void OnShow() {
        super.OnShow();

        UpdateDzlValues();
    }

    override void Update(float timeslice) {
        super.Update(timeslice);
        UpdateDzlValues();
    }

    private void UpdateDzlValues() {
        DZLPlayer dzlPlayer = DZLPlayerBaseHelper.GetPlayer().GetDZLPlayer();

        if (dzlPlayer) {
            moneyAtBank.SetText(dzlPlayer.GetBankMoney().ToString());
            moneyAtPlayer.SetText(dzlPlayer.GetMoney().ToString());
            playerArrest.SetText(dzlPlayer.arrestTimeInMinutes.ToString());
        }
    }
}
