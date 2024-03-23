class DZLShopActionObject: DZLBaseActionObject {

    void DZLShopActionObject() {
        isShopActionPoint = true;
    }

    override void SetActions() {
        super.SetActions();

        AddAction(DZLActionRobShop);
        AddAction(DZLActionTakeRobtMoneyShop);
    }
}