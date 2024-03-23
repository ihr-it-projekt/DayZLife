class DZLBankAutomate_Red: DZLBaseActionObject {
    void DZLBankAutomate_Red() {
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