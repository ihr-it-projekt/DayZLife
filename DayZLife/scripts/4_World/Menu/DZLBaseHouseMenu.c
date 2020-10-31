class DZLBaseHouseMenu: DZLBaseMenu
{
    protected ref DZLHouseDefinition actualHouseDef;
    protected ref DZLBuilding house;
    protected Building target;
    protected ref DZLPreviewWindow preview;

    protected ButtonWidget buyButton;
    protected ButtonWidget sellButton;
    protected TextWidget priceBuyTextWidget;
    protected TextWidget priceSellTextWidget;
    protected TextWidget balanceTextWidget;
    protected TextWidget storageTextWidget;

    override protected void Construct() {
        super.Construct();
    }

    void SetTarget(Building target) {
        this.target = target;
        Param2<PlayerBase,ref Building> paramGetBuildingProperties = new Param2<PlayerBase,ref Building>(player, this.target);
        GetGame().RPCSingleParam(paramGetBuildingProperties.param1, DAY_Z_LIFE_OPEN_GET_BUILDING_DATA, paramGetBuildingProperties, true);
    }

	void SetHouseDefinition(DZLHouseDefinition definition) {
		actualHouseDef = definition;
	}

    override void UpdateGUI(string message = "") {
        balanceTextWidget.SetText(dzlPlayer.money.ToString());
        super.UpdateGUI(message);
    }

    override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_OPEN_GET_BUILDING_DATA_RESPONSE) {
            autoptr Param1<ref DZLBuilding> paramGetBuildingProperties;
            if (ctx.Read(paramGetBuildingProperties)){
                house = paramGetBuildingProperties.param1;
                UpdateGUI();
            }
        }
    }

    override Widget Init() {
        super.Init();

        sellButton = creator.GetButtonWidget("Button_Sell");
        sellButton.Show(false);

        buyButton = creator.GetButtonWidget("Button_Buy");
        buyButton.Show(false);

        preview = new DZLPreviewWindow(creator.GetItemPreviewWidget("Preview"));

        priceBuyTextWidget = creator.GetTextWidget("Price_Buy");
        priceSellTextWidget = creator.GetTextWidget("Price_Sell");
        balanceTextWidget = creator.GetTextWidget("Balance");
        
        storageTextWidget = creator.GetTextWidget("Number_of_Storage");

        return layoutRoot;
    }
	
	override void OnShow() {
        if (actualHouseDef) {
            super.OnShow();
            balanceTextWidget.SetText(dzlPlayer.money.ToString());
        } else {
            OnHide();
        }
    }

}