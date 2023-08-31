class DZLTraderActionObject: DZLBaseActionObject
{
    void DZLTraderActionObject() {
		isTrader = true;
	}


    override void SetActions()
    {
        super.SetActions();

        AddAction(ActionOpenTraderMenu);
    }
}