class DLBuyHouseMenu : UIScriptedMenu
{
	protected static ref DLBuyHouseMenu instance;
	
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
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("DayZLife/layout/Housing/Housing.layout");

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
	
	override void Update(float timeslice)
	{
		super.Update(timeslice);
		

	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{
		super.OnClick(w, x, y, button);
	
		switch(w)
		{

		}
		return false;
	}
	
	override bool OnDoubleClick( Widget w, int x, int y, int button )
	{
		super.OnDoubleClick(w, x, y, button);
	
		switch(w)
		{

		}
		return false;
	}
	

	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		super.OnChange(w,x,y,finished);
		
		switch(w)
		{

        }
        return false;
	}

}