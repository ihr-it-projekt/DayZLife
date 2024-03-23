class DZLBankAutomate_Yellow: DZLBaseActionObject {
    void DZLBankAutomate_Yellow() {
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