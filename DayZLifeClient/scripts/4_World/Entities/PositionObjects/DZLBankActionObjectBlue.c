class DZLBankAutomate_Blue: DZLBaseActionObject {
    void DZLBankAutomate_Blue() {
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