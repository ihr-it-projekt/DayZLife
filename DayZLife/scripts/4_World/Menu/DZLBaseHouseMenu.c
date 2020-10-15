class DZLBaseHouseMenu : UIScriptedMenu
{
    protected ref DZLUIItemCreator creator;
    protected ref DZLConfig config;
    protected ref DZLPlayerInventory inventory;
    protected ref DZLHouseDefinition actualHouseDef;
    protected ref DZLBuilding house;
    protected Building target;
    protected ref DZLPreviewWindow preview;
    protected string layoutPath;


    ButtonWidget closeButton;
    ButtonWidget buyButton;
    ButtonWidget sellButton;
    TextWidget priceBuyTextWidget;
    TextWidget priceSellTextWidget;
    TextWidget balanceTextWidget;
    TextWidget errorMessageTextWidget;
    TextWidget storageTextWidget;


    protected void Construct() {
        if(GetGame().IsClient()){
            inventory = new DZLPlayerInventory();
            GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
        }
    }

    protected void Destruct() {
        OnHide();
        DebugMessageDZL("Destroy Buy menu");
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void SetConfig(ref DZLConfig config) {
        this.config = config;
        inventory.SetConfig(this.config.moneyConfig.currencyValues);
    }

    void SetTarget(Building target) {
        this.target = target;
        Param2<PlayerBase,ref Building> paramGetBuildingProperties = new Param2<PlayerBase,ref Building>(GetGame().GetPlayer(), this.target);
        GetGame().RPCSingleParam(paramGetBuildingProperties.param1, DAY_Z_LIFE_OPEN_GET_BUILDING_DATA, paramGetBuildingProperties, true);
    }

	void SetHouseDefinition(DZLHouseDefinition definition) {
		actualHouseDef = definition;
	}

    void UpdateGUI(string message = "") {
        balanceTextWidget.SetText(inventory.GetPlayerMoneyAmount(GetGame().GetPlayer()).ToString());
        if(message) errorMessageTextWidget.SetText(message);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_OPEN_GET_BUILDING_DATA_RESPONSE) {
            autoptr Param1<ref DZLBuilding> paramGetBuildingProperties;
            if (ctx.Read(paramGetBuildingProperties)){
                house = paramGetBuildingProperties.param1;
                UpdateGUI();
            }
        }
    }

    override Widget Init() {
        creator = new DZLUIItemCreator(layoutPath);

        closeButton = creator.GetButtonWidget("Button_Closed");
        closeButton.Show(true);

        sellButton = creator.GetButtonWidget("Button_Sell");
        sellButton.Show(false);

        buyButton = creator.GetButtonWidget("Button_Buy");
        buyButton.Show(false);

        preview = new DZLPreviewWindow(creator.GetItemPreviewWidget("Preview"));

        priceBuyTextWidget = creator.GetTextWidget("Price_Buy");
        priceSellTextWidget = creator.GetTextWidget("Price_Sell");
        balanceTextWidget = creator.GetTextWidget("Balance");
        errorMessageTextWidget = creator.GetTextWidget("Error_Message");
        storageTextWidget = creator.GetTextWidget("Number_of_Storage");

        layoutRoot = creator.GetLayoutRoot();

        layoutRoot.Show(false);

        return layoutRoot;
    }

    override void OnShow() {
        if (actualHouseDef) {
            super.OnShow();

            preview.UpdatePreview(actualHouseDef.houseType);
            errorMessageTextWidget.SetText("");
            balanceTextWidget.SetText(inventory.GetPlayerMoneyAmount(GetGame().GetPlayer()).ToString());
        }

        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_INVENTORY);
        GetGame().GetUIManager().ShowCursor(true);
        GetGame().GetInput().ChangeGameFocus(1);
    }

    override void OnHide() {
        super.OnHide();

        GetGame().GetUIManager().ShowCursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(true);
        Close();
    }

}