class DZLBuyHouseMenu : UIScriptedMenu
{
	private ref DZLUIItemCreator creator;
	private ref DZLConfig config;
	private ref DZLPlayerInventory inventory;
	private ref DZLHouseFinder houseFinder;
	private ref DZLHouseDefinition actualHouseDef;

	ButtonWidget closeButton;
	ButtonWidget buyButton;
	ButtonWidget sellButton;
	MapWidget mapWidget;
	TextWidget priceBuyTextWidget;
	TextWidget priceSellTextWidget;
	TextWidget storageTextWidget;
	
	
	void DZLBuyHouseMenu()
	{
		if(GetGame().IsClient()){
			houseFinder = new DZLHouseFinder();
			inventory = new DZLPlayerInventory();

			DebugMessageDZL("Create Buy menu");
		}
	}
	
	void ~DZLBuyHouseMenu()
	{
        OnHide();
        DebugMessageDZL("Destroy Buy menu");

	}

	void SetConfig(ref DZLConfig config) {
        this.config = config;
	    inventory.SetConfig(this.config.moneyConfig.currencyValues);
        houseFinder.SetConfig(this.config);
	}

	override Widget Init()
    {
		creator = new DZLUIItemCreator("DayZLife/layout/Housing/Housing.layout");
		
		closeButton = creator.GetButtonWidget("Button_Closed");
		closeButton.Show(true);
		
		sellButton = creator.GetButtonWidget("Button_Sell");
		sellButton.Show(false);
		
		buyButton = creator.GetButtonWidget("Button_Buy");
		buyButton.Show(true);
		
		mapWidget = creator.GetMapWidget("Map");
		
		priceBuyTextWidget = creator.GetTextWidget("Price_Buy");
		priceSellTextWidget = creator.GetTextWidget("Price_Sell");
		storageTextWidget = creator.GetTextWidget("Number_of_Storage");
		
		layoutRoot = creator.GetLayoutRoot();

		layoutRoot.Show(false);
		
	    return layoutRoot;
    }
	
	override void OnShow()
	{
	    actualHouseDef = houseFinder.find();
        if (actualHouseDef) {
            DebugMessageDZL("has house def " + actualHouseDef.houseType);
            super.OnShow();

            priceBuyTextWidget.SetText(actualHouseDef.buyPrice.ToString());
            priceSellTextWidget.SetText(actualHouseDef.sellPrice.ToString());
            storageTextWidget.SetText(actualHouseDef.countStorage.ToString());
        } else {
            DebugMessageDZL("can not show, now house deff");
        }

		GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_INVENTORY);
        GetGame().GetUIManager().ShowCursor(true);
        GetGame().GetInput().ChangeGameFocus(1);
	}
	
	override void OnHide()
	{
		super.OnHide();

        GetGame().GetUIManager().ShowCursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(true);
		Close();
	}
	

	override bool OnClick( Widget w, int x, int y, int button )
	{
		super.OnClick(w, x, y, button);
	
		switch(w){
            case closeButton:
                OnHide();
                return true;
            case buyButton:

			
				DebugMessageDZL("has house found");
                if (inventory.PlayerHasEnoughMoney(GetGame().GetPlayer(), actualHouseDef.buyPrice)) {
					DebugMessageDZL("Can send buy request");
			
				}
                // buy logic
                return true;
            case sellButton:
                // sell logic
                return true;
		}
		return false;
	}



}