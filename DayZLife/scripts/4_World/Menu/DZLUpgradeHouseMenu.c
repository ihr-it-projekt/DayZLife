class DZLUpgradeHouseMenu : DZLBaseHouseMenu
{
	TextListboxWidget storageListTextWidget;
	TextListboxWidget sellStorageListTextWidget;

	
	void DZLUpgradeHouseMenu()
	{
		Construct();
	}
	
	void ~DZLUpgradeHouseMenu()
	{
        Destruct();
	}

	override Widget Init()
    {
        layoutPath = "DayZLife/layout/Housing/Housing_upgrade.layout";
		super.Init();
		storageListTextWidget = creator.GetTextListboxWidget("Storage_List");
		sellStorageListTextWidget = creator.GetTextListboxWidget("Sell_Storage_List");

	    return layoutRoot;
    }
	

	override void OnShow()
	{
        super.OnShow();

        storageListTextWidget.ClearItems();
        sellStorageListTextWidget.ClearItems();
	    if (actualHouseDef) {
	        priceBuyTextWidget.SetText("");
            priceSellTextWidget.SetText("");
            storageTextWidget.SetText("");

			foreach(DZLStorageType storageType: config.GetStorageTypes()) {
				storageListTextWidget.AddItem(storageType.type, storageType, 0);
			}

            if (house) {
                int x = 1;
                foreach(DZLStorageTypeBought storage: house.GetStorage()) {
                    sellStorageListTextWidget.AddItem(storage.storageType.type, storage, 0);
                }
            }
        }
	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{
		super.OnClick(w, x, y, button);
	
		switch(w){
            case closeButton:
                OnHide();
                return true;
            case storageListTextWidget:
                DebugMessageDZL("Click on 1");

                return true;
            case sellStorageListTextWidget:
			
                DebugMessageDZL("Click on 2");

                return true;
            case buyButton:

                return true;
            case sellButton:

                return true;
		}
		return false;
	}

	override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
	    super.HandleEventsDZL(sender, target, rpc_type, ctx);


    }
	
	override void UpdateGUI(string message = "") {
	    super.UpdateGUI(message);
		if (house && house.IsOwner(PlayerBaseHelper.GetPlayer())) {
			sellButton.Show(true);
			buyButton.Show(false);
			errorMessageTextWidget.SetText("");
		} else if (house && house.HasOwner() && !house.IsOwner(PlayerBaseHelper.GetPlayer())) {
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