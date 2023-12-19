class DZLShopActionObject: DZLBaseActionObject {

    void DZLShopActionObject() {
        isShopActionPoint = true;
    }

    override void SetActions() {
        super.SetActions();

        AddAction(ActionRobShop);
        AddAction(ActionTakeRobtMoneyShop);
    }
}