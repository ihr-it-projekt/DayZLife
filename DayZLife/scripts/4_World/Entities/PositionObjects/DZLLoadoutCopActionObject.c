class DZLLoadoutCopActionObject: DZLBaseActionObject
{
    void DZLLoadoutCopActionObject() {
		this.isCopLoadOut = true;
	}

	override void SetActions() {
        super.SetActions();

        AddAction(ActionOpenLoadOutMenu);
    }
}