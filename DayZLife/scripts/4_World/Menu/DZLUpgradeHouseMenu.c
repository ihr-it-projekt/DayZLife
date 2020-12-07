class DZLUpgradeHouseMenu : DZLBaseHouseMenu
{
	TextListboxWidget extensionListTextWidget;
	TextListboxWidget sellStorageListTextWidget;
	TextWidget alarmLevel;
	MultilineTextWidget description;

	void DZLUpgradeHouseMenu(){
		Construct();
	}
	
	void ~DZLUpgradeHouseMenu(){
        Destruct();
	}

	override Widget Init(){
        layoutPath = "DayZLife/layout/Housing/Housing_upgrade.layout";
		super.Init();
		extensionListTextWidget = creator.GetTextListboxWidget("Storage_List");
		sellStorageListTextWidget = creator.GetTextListboxWidget("Sell_Storage_List");
		description = creator.GetMultilineTextWidget("discription");
		alarmLevel = creator.GetTextWidget("alarmsystemlvl");

	    return layoutRoot;
    }
	

	override void OnShow(){
        extensionListTextWidget.ClearItems();
        sellStorageListTextWidget.ClearItems();
	    if (actualHouseDef) {
	        super.OnShow();
	        priceBuyTextWidget.SetText("");
            priceSellTextWidget.SetText("");
            alarmLevel.SetText("0");
        }
	}
	
	override bool OnClick(Widget w, int x, int y, int button){
		if(super.OnClick(w, x, y, button)) return true;
	
		switch(w){
            case extensionListTextWidget:
				int itemPos = extensionListTextWidget.GetSelectedRow();

				if (-1 == itemPos) return true;

				DZLHouseExtension currentItem;
				extensionListTextWidget.GetItemData(itemPos, 0, currentItem);
			
				if (!currentItem) return true;

                int buyPrice = currentItem.price;
                int sellPrice = 0;
                bool showBuyButton = true;

                description.SetText(currentItem.description);

                if (currentItem.isStorage) {
                    int itemsHasBought = sellStorageListTextWidget.GetNumItems() + 1;

                    preview.UpdatePreview(currentItem.type);

                    buyPrice =  currentItem.price * (actualHouseDef.storageBuyFactor * itemsHasBought);

                    sellPrice =  buyPrice / 2;

                    sellButton.Show(false);
                    showBuyButton = actualHouseDef.GetMaxStorage() > house.GetStorage().Count();

                    if (actualHouseDef.GetMaxStorage() <= house.GetStorage().Count()) {
                        player.DisplayMessage("#building_has_all_storrage_positions_upgraded");
                    }
                }

                priceBuyTextWidget.SetText(buyPrice.ToString());
                priceSellTextWidget.SetText(sellPrice.ToString());
                buyButton.Show(showBuyButton);
			
                return true;
            case sellStorageListTextWidget:
			
                int itemPosSell = sellStorageListTextWidget.GetSelectedRow();
				
				if (-1 == itemPosSell) return true;
			
				DZLStorageTypeBought currentItemSell;
				sellStorageListTextWidget.GetItemData(itemPosSell, 0, currentItemSell);
			
				if (!currentItemSell) return true;
			
				preview.UpdatePreview(currentItemSell.type);
			
				priceBuyTextWidget.SetText(currentItemSell.paidPrice.ToString());
				priceSellTextWidget.SetText(currentItemSell.sellPrice.ToString());
			
				buyButton.Show(false);
				sellButton.Show(true);

                return true;
            case buyButton:
				int itemPosBuy = extensionListTextWidget.GetSelectedRow();
				DZLHouseExtension currentItemBuy;
				extensionListTextWidget.GetItemData(itemPosBuy, 0, currentItemBuy);
			
				if (!currentItemBuy) {
				    return true;
				}

			    int buyPriceBuy = 0;
				bool canBuy = false;
				PlayerBase playerBaseBuy = PlayerBaseHelper.GetPlayer();

			    if (currentItemBuy.isStorage) {
				    buyPriceBuy =  currentItemBuy.price * (actualHouseDef.storageBuyFactor * (itemsHasBought + 1));
				    canBuy = actualHouseDef.GetMaxStorage() > sellStorageListTextWidget.GetNumItems();
                } else {
                    buyPriceBuy = currentItemBuy.price;
                    canBuy = dzlPlayer.HasEnoughMoney(buyPriceBuy) && house.IsOwner(playerBaseBuy) && house.CanBuyAlarm(currentItemBuy);
                }

				if (canBuy) {
					GetGame().RPCSingleParam(playerBaseBuy, DAY_Z_LIFE_BUY_EXTENSION, new Param3<PlayerBase, ref Building, string>(playerBaseBuy, target, currentItemBuy.id), true);
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
		
		if (rpc_type == DAY_Z_LIFE_BUY_EXTENSION_RESPONSE || rpc_type == DAY_Z_LIFE_SELL_STORAGE_RESPONSE) {
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
			extensionListTextWidget.ClearItems();
			if (house.HasAlarmSystem()) {
				alarmLevel.SetText(house.GetHouseAlarm().level.ToString());
			}
            
            array<ref DZLHouseExtension> extensions = config.GetExtensions();
            foreach(DZLHouseExtension extension: extensions) {
                string name = "";
                if (extension.isStorage) {
                    name = DZLDisplayHelper.GetItemDisplayName(extension.type);
                } else if(extension.isHouseAlarm) {
                   	if (house.CanBuyAlarm(extension)) {
						name = extension.type;
                    }
                }

                if (name) {
                    extensionListTextWidget.AddItem(name, extension, 0);
                }
            }

			sellStorageListTextWidget.ClearItems();
            array<ref DZLStorageTypeBought> storagesBought = house.GetStorage();
            foreach(DZLStorageTypeBought storageBought: storagesBought) {
                sellStorageListTextWidget.AddItem(DZLDisplayHelper.GetItemDisplayName(storageBought.storageType.type), storageBought, 0);
            }

            sellButton.Show(false);
			buyButton.Show(false);
        }
	}
}
