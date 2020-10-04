class DZLBuyHouseMenu : UIScriptedMenu
{
	private static ref DZLBuyHouseMenu instance;
	private ref DZLUIItemCreator creator;
	private DZLServerConfig config;
	private ref DZLPlayerInventory inventory;
	private ref DZLObjectFinder objectFinder;
	
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
			
		}
	}
	
	void ~DZLBuyHouseMenu()
	{
        GetGame().GetUIManager().ShowCursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(true);
	}
	
	static DZLBuyHouseMenu GetInstance(DZLServerConfig configExt = null)
	{
		if (!instance && configExt)
        {
            instance = new DZLBuyHouseMenu();
			instance.Init();
			instance.SetConfig(configExt);
        }
		return instance;
	}
	
	void SetConfig(DZLServerConfig config) {
		this.config = config;

		inventory = new DZLPlayerInventory(this.config.moneyConfig.currencyValues);
		objectFinder = new DZLObjectFinder(this.config.houseConfig);
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
		super.OnShow();
		
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
				DayZPlayer player = GetGame().GetPlayer();
				Object object = objectFinder.GetObjectsAt(player.GetPosition(), player);
				
				if (!object) {
					return true;
				}
				
				Building house = Building.Cast(object);
				DZLHouseDefinition actualHouseDef;
			
				foreach(DZLHouseDefinition houseDef: config.houseConfig.houseConfigs) {
					if(house.GetType() == houseDef.houseType) {
						actualHouseDef = houseDef;
						break;
					}
				}
			
				if (!actualHouseDef) {
					return true;
				}
			
                if (inventory.PlayerHasEnoughMoney(player, actualHouseDef.price)) {
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