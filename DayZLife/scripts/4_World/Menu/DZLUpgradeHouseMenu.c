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

	override Widget Init(){
        layoutPath = "DayZLife/layout/Housing/Housing_upgrade.layout";
		super.Init();
		storageListTextWidget = creator.GetTextListboxWidget("Storage_List");
		sellStorageListTextWidget = creator.GetTextListboxWidget("Sell_Storage_List");

	    return layoutRoot;
    }
	

	override void OnShow(){
        super.OnShow();

        storageListTextWidget.ClearItems();
        sellStorageListTextWidget.ClearItems();
	    if (actualHouseDef) {
	        priceBuyTextWidget.SetText("");
            priceSellTextWidget.SetText("");
            storageTextWidget.SetText("");

            if (config) {
				array<ref DZLStorageType> storageTypes = config.GetStorageTypes();
                foreach(DZLStorageType storageType: storageTypes) {
                    storageListTextWidget.AddItem(DZLDisplayHelper.GetItemDisplayName(storageType.type), storageType, 0);
                }
            }

            if (house) {
				array<ref DZLStorageTypeBought> storages = house.GetStorage();
                foreach(DZLStorageTypeBought storage: storages) {
                    sellStorageListTextWidget.AddItem(DZLDisplayHelper.GetItemDisplayName(storage.storageType.type), storage, 0);
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
				int itemPos = storageListTextWidget.GetSelectedRow();

				DebugMessageDZL("Has row " + itemPos.ToString());

				if (-1 == itemPos) return true;

				DZLStorageType currentItem;
				storageListTextWidget.GetItemData(itemPos, 0, currentItem);
			
				if (!currentItem) return true;

				DebugMessageDZL("Has type " + currentItem.type);
			
				int itemsHasBought = sellStorageListTextWidget.GetNumItems() + 1;
			
				preview.UpdatePreview(currentItem.type);
			
				int buyPrice =  currentItem.price * (actualHouseDef.storageBuyFactor * itemsHasBought);
			
				DebugMessageDZL("Buy price " + buyPrice.ToString());
			
				priceBuyTextWidget.SetText(buyPrice.ToString());
			
				int sellPrice =  buyPrice / 2;
				DebugMessageDZL("sellPrice price " + sellPrice.ToString());
			
				priceSellTextWidget.SetText(sellPrice.ToString());
			
				storageTextWidget.SetText(currentItem.space.ToString());
				
				sellButton.Show(false);
				buyButton.Show(actualHouseDef.GetMaxStorage() > house.GetStorage().Count());
				
				if (actualHouseDef.GetMaxStorage() <= house.GetStorage().Count()) {
					errorMessageTextWidget.SetText("#building_has_all_storrage_positions_upgraded");
				}
			
			
                return true;
            case sellStorageListTextWidget:
			
                int itemPosSell = sellStorageListTextWidget.GetSelectedRow();
				
				DebugMessageDZL("Has row " + itemPosSell.ToString());
			
				if (-1 == itemPosSell) return true;
			
				DZLStorageTypeBought currentItemSell;
				sellStorageListTextWidget.GetItemData(itemPosSell, 0, currentItemSell);
			
				if (!currentItemSell) return true;
			
				DebugMessageDZL("Has type " + currentItemSell.type);
			
				preview.UpdatePreview(currentItemSell.type);
			
				priceBuyTextWidget.SetText(currentItemSell.paidPrice.ToString());
				priceSellTextWidget.SetText(currentItemSell.sellPrice.ToString());
				storageTextWidget.SetText(currentItemSell.storageType.space.ToString());
			
				buyButton.Show(false);
				sellButton.Show(true);

                return true;
            case buyButton:
				int itemPosBuy = storageListTextWidget.GetSelectedRow();
				DZLStorageType currentItemBuy;
				storageListTextWidget.GetItemData(itemPosBuy, 0, currentItemBuy);
			
				if (!currentItemBuy) {
				    DebugMessageDZL("not found currentItemBuy");
				    return true;
				}
			
				
				int buyPriceBuy =  currentItemBuy.price * (actualHouseDef.storageBuyFactor * (itemsHasBought + 1));
				PlayerBase playerBaseBuy = PlayerBaseHelper.GetPlayer();
				if (actualHouseDef.GetMaxStorage() > sellStorageListTextWidget.GetNumItems() && inventory.PlayerHasEnoughMoney(PlayerBaseHelper.GetPlayer(), buyPriceBuy) && house.IsOwner(playerBaseBuy)) {
					GetGame().RPCSingleParam(playerBaseBuy, DAY_Z_LIFE_BUY_STORAGE, new Param3<PlayerBase, ref Building, ref DZLStorageType>(playerBaseBuy, target, currentItemBuy), true);
				}
				
			
                return true;
            case sellButton:
				int itemPosStorageSell = sellStorageListTextWidget.GetSelectedRow();
				DZLStorageTypeBought currentItemStorageSell;
				sellStorageListTextWidget.GetItemData(itemPosStorageSell, 0, currentItemStorageSell);
			
				if (!currentItemStorageSell) return true;

				PlayerBase playerBaseSell = PlayerBaseHelper.GetPlayer();
				if (house.IsOwner(playerBaseSell)) {
					GetGame().RPCSingleParam(playerBaseSell, DAY_Z_LIFE_SELL_STORAGE, new Param3<PlayerBase, ref Building, vector>(playerBaseSell, target, currentItemStorageSell.position), true);
				}

                return true;
		}
		return false;
	}

	override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
	    super.HandleEventsDZL(sender, target, rpc_type, ctx);
		
		if (rpc_type == DAY_Z_LIFE_BUY_STORAGE_RESPONSE || rpc_type == DAY_Z_LIFE_SELL_STORAGE_RESPONSE) {
            autoptr Param2<ref DZLBuilding, string> paramBuyStorageResponse;
            if (ctx.Read(paramBuyStorageResponse)){
				house = paramBuyStorageResponse.param1;
				
				UpdateGUI(paramBuyStorageResponse.param2);
	        }
        }
    }
	
	override void UpdateGUI(string message = "") {
	    super.UpdateGUI(message);
		
		if (house) {
			sellStorageListTextWidget.ClearItems();
            array<ref DZLStorageTypeBought> storages = house.GetStorage();
            foreach(DZLStorageTypeBought storage: storages) {
                sellStorageListTextWidget.AddItem(DZLDisplayHelper.GetItemDisplayName(storage.storageType.type), storage, 0);
            }

            sellButton.Show(false);
			
			if (buyButton.IsVisible()) buyButton.Show(actualHouseDef.GetMaxStorage() > storages.Count());
        }
		
	}

}