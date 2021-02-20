class DZLBankActionObjectBlue: DZLBaseActionObject
{
    void DZLBankActionObjectBlue() {
		isBank = true;
	}

	override void SetActions() {
        super.SetActions();

        AddAction(ActionOpenBankingMenu);
        AddAction(ActionRobBank);
        AddAction(DZLActionPaybackRobtMoney);
        AddAction(ActionStopRobBank);
        AddAction(ActionTakeRobbtMoneyBank);
    }
}