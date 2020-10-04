class DLBuyHouseMenu : UIScriptedMenu
{
	private static ref DLBuyHouseMenu instance;
	private ref DZLUIItemCreator creator;
	
	ButtonWidget closeButton;
	ButtonWidget buyButton;
	ButtonWidget sellButton;
	MapWidget mapWidget;
	TextWidget priceBuyTextWidget;
	TextWidget priceSellTextWidget;
	TextWidget storageTextWidget;
	
	
	void DLBuyHouseMenu()
	{
		if(GetGame().IsClient()){
			
		}
	}
	
	void ~DLBuyHouseMenu()
	{
        GetGame().GetUIManager().ShowCursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(true);
	}
	
	static DLBuyHouseMenu GetInstance()
	{
		if (!instance)
        {
            instance = new DLBuyHouseMenu();
			instance.Init();
        }
		return instance;
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
		buyButton.Show(false);
		
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
                // buy logic
                return true;
            case sellButton:
                // sell logic
                return true;
		}
		return false;
	}
}