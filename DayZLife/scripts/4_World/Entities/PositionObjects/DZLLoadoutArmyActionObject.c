class DZLLoadoutArmyActionObject: DZLBaseActionObject
{
    void DZLLoadoutArmyActionObject() {
		this.isArmyLoadOut = true;
	}

	override void SetActions() {
        super.SetActions();

        AddAction(ActionOpenLoadOutMenu);
    }
}