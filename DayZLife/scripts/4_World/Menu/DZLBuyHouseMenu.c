class DZLBuyHouseMenu : UIScriptedMenu
{
	private static ref DZLBuyHouseMenu instance;
	private ref DZLUIItemCreator creator;
	private DZLServerConfig config;
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
			GetDayZGame().Event_OnRPC.Insert(HandleEvents);
		
			Param1<DayZPlayer> paramGetConfig = new Param1<DayZPlayer>(GetGame().GetPlayer());
	        GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_EVENT_GET_CONFIG, paramGetConfig, true);
			houseFinder = new DZLHouseFinder();
			inventory = new DZLPlayerInventory();
		}
	}
	
	void ~DZLBuyHouseMenu()
	{
        GetGame().GetUIManager().ShowCursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(true);
		
		GetDayZGame().Event_OnRPC.Remove(HandleEvents);
	}
	
	static DZLBuyHouseMenu GetInstance()
	{
		if (!instance)
        {
            instance = new DZLBuyHouseMenu();
			instance.Init();
        }
		return instance;
	}
	
	void SetConfig(DZLServerConfig config) {
		this.config = config;


		
	}
	
	static void ClearInstance()
	{
		instance = null;
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
		if (config) {
			actualHouseDef = houseFinder.find();
			if (actualHouseDef) {
			    DebugMessageDZL("has house def " + actualHouseDef.houseType);
		        super.OnShow();
				
				priceBuyTextWidget.SetText(actualHouseDef.buyPrice.ToString());
				priceSellTextWidget.SetText(actualHouseDef.sellPrice.ToString());
				storageTextWidget.SetText(actualHouseDef.countStorage.ToString());
	
	            GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_INVENTORY);
	            GetGame().GetUIManager().ShowCursor(true);
	            GetGame().GetInput().ChangeGameFocus(1);
	        }
		}

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
	
	void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
   		if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE) {
		
			DebugMessageDZL("GET config");
   			Param1 <ref DZLServerConfig> configParam;
   			if (ctx.Read(configParam)){
				this.config = configParam.param1;
				inventory.SetConfig(this.config.moneyConfig.currencyValues);
				houseFinder.SetConfig(this.config);
   			}
   		}
   	}


}