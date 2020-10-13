class DZLBuyHouseMenu : UIScriptedMenu
{
	private ref DZLUIItemCreator creator;
	private ref DZLConfig config;
	private ref DZLPlayerInventory inventory;
	private ref DZLHouseDefinition actualHouseDef;
	private ref DZLBuilding house;
	private Building target;

	ButtonWidget closeButton;
	ButtonWidget buyButton;
	ButtonWidget sellButton;
	MapWidget mapWidget;
	TextWidget priceBuyTextWidget;
	TextWidget priceSellTextWidget;
	TextWidget balanceTextWidget;
	TextWidget errorMessageTextWidget;
	TextWidget storageTextWidget;
	ref DZLPreviewWindow preview;
	
	
	void DZLBuyHouseMenu()
	{
		if(GetGame().IsClient()){
			inventory = new DZLPlayerInventory();
            GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
            
			DebugMessageDZL("Create Buy menu");
		}
	}
	
	void ~DZLBuyHouseMenu()
	{
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

	override Widget Init()
    {
		creator = new DZLUIItemCreator("DayZLife/layout/Housing/Housing.layout");
		
		closeButton = creator.GetButtonWidget("Button_Closed");
		closeButton.Show(true);
		
		sellButton = creator.GetButtonWidget("Button_Sell");
		sellButton.Show(false);
		
		buyButton = creator.GetButtonWidget("Button_Buy");
		buyButton.Show(false);
		
		mapWidget = creator.GetMapWidget("Map");
		
		preview = new DZLPreviewWindow(creator.GetItemPreviewWidget("Hous_Preview"));
		
		priceBuyTextWidget = creator.GetTextWidget("Price_Buy");
		priceSellTextWidget = creator.GetTextWidget("Price_Sell");
		balanceTextWidget = creator.GetTextWidget("Balance");
		errorMessageTextWidget = creator.GetTextWidget("Error_Message");
		storageTextWidget = creator.GetTextWidget("Number_of_Storage");
		

		
		layoutRoot = creator.GetLayoutRoot();

		layoutRoot.Show(false);
		
	    return layoutRoot;
    }
	
	void SetHouseDefinition(DZLHouseDefinition definition) {
		actualHouseDef = definition;
	}
	
	override void OnShow()
	{
	    if (actualHouseDef) {
            DebugMessageDZL("has house def " + actualHouseDef.houseType);
            super.OnShow();
            priceBuyTextWidget.SetText(actualHouseDef.buyPrice.ToString());
            priceSellTextWidget.SetText(actualHouseDef.sellPrice.ToString());
            storageTextWidget.SetText(actualHouseDef.countMaxStorage.ToString());
			preview.UpdatePreview(actualHouseDef.houseType);
			mapWidget.SetMapPos(target.GetPosition());
			mapWidget.SetScale(0.2);
			errorMessageTextWidget.SetText("");
			balanceTextWidget.SetText(inventory.GetPlayerMoneyAmount(GetGame().GetPlayer()).ToString());
			
        } else {
            DebugMessageDZL("can not show, no house def");
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

	void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_OPEN_GET_BUILDING_DATA_RESPONSE) {
            autoptr Param1<ref DZLBuilding> paramGetBuildingProperties;
            if (ctx.Read(paramGetBuildingProperties)){
				house = paramGetBuildingProperties.param1;

				if (!house) {
				    DebugMessageDZL("receive building data no data");
				}

				DebugMessageDZL("receive building data" + house.HasOwner());
				UpdateGUI();
	        }
        }
    }
	
	void UpdateGUI() {
		if (house && house.HasOwner() && house.IsOwner(GetGame().GetPlayer())) {
			sellButton.Show(true);
			buyButton.Show(false);
			errorMessageTextWidget.SetText("");
		} else if (house && house.HasOwner() && !house.IsOwner(GetGame().GetPlayer())) {
			sellButton.Show(false);
			buyButton.Show(false);
			errorMessageTextWidget.SetText("#building_has_already_an_owner");
		} else if (house && !house.HasOwner()) {
			sellButton.Show(false);
			buyButton.Show(true);
			errorMessageTextWidget.SetText("");
		} else if (!house) {
			sellButton.Show(false);
			buyButton.Show(false);
			errorMessageTextWidget.SetText("");
		}
	}

}