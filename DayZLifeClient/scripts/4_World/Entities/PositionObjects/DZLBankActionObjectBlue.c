class DZLBankActionObjectBlue: DZLBaseActionObject {
    void DZLBankActionObjectBlue() {
        isBank = true;
    }

    override void SetActions() {
        super.SetActions();

        AddAction(DZLActionOpenBankingMenu);
        AddAction(ActionRobBank);
        AddAction(DZLActionPaybackRobtMoney);
        AddAction(ActionStopRobBank);
        AddAction(ActionTakeRobtMoneyBank);
    }
}