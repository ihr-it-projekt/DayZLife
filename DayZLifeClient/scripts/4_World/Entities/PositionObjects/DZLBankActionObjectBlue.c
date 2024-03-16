class DZLBankActionObjectBlue: DZLBaseActionObject {
    void DZLBankActionObjectBlue() {
        isBank = true;
    }

    override void SetActions() {
        super.SetActions();

        AddAction(DZLActionOpenBankingMenu);
        AddAction(DZLActionRobBank);
        AddAction(DZLActionPaybackRobtMoney);
        AddAction(DZLActionStopRobBank);
        AddAction(DZLActionTakeRobtMoneyBank);
    }
}