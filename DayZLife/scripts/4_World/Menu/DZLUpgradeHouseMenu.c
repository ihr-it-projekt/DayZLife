class DZLUpgradeHouseMenu : DZLBaseHouseMenu
{
	TextListboxWidget extensionListTextWidget;
	TextListboxWidget sellStorageListTextWidget;
	TextWidget alarmLevel;

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
			
			if (!config) {
				DebugMessageDZL("no config");
			}
			if (!house) {
				DebugMessageDZL("no house");
			}


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

                if (currentItem.isStorage) {
                    int itemsHasBought = sellStorageListTextWidget.GetNumItems() + 1;

                    preview.UpdatePreview(currentItem.type);

                    buyPrice =  currentItem.price * (actualHouseDef.storageBuyFactor * itemsHasBought);

                    priceBuyTextWidget.SetText(buyPrice.ToString());

                    sellPrice =  buyPrice / 2;

                    sellButton.Show(false);
                    showBuyButton = actualHouseDef.GetMaxStorage() > house.GetStorage().Count();

                    if (actualHouseDef.GetMaxStorage() <= house.GetStorage().Count()) {
                        player.DisplayMessage("#building_has_all_storrage_positions_upgraded");
                    }
                }

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

			    int buyPriceBuy = currentItemBuy.price;
				PlayerBase playerBaseBuy = PlayerBaseHelper.GetPlayer();
				bool canBuy = dzlPlayer.HasEnoughMoney(buyPriceBuy) && house.IsOwner(playerBaseBuy);

			    if (currentItem.isStorage) {
				    buyPriceBuy =  currentItemBuy.price * (actualHouseDef.storageBuyFactor * (itemsHasBought + 1));
				    canBuy = actualHouseDef.GetMaxStorage() > sellStorageListTextWidget.GetNumItems() && canBuy;
                }

				if (canBuy) {
					GetGame().RPCSingleParam(playerBaseBuy, DAY_Z_LIFE_BUY_EXTENSION, new Param3<PlayerBase, ref Building, ref DZLHouseExtension>(playerBaseBuy, target, currentItemBuy), true);
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
			if (house.HasAlarmSystem()) {
				alarmLevel.SetText(house.GetHouseAlarm().level.ToString());
			}
            
            array<ref DZLHouseExtension> extensions = config.GetExtensions();
            foreach(DZLHouseExtension extension: extensions) {
                string name = "";
                if (extension.isStorage) {
                    name = DZLDisplayHelper.GetItemDisplayName(extension.type);
                } else if(extension.isHouseAlarm) {
                    DZLHouseAlarm alarm = DZLHouseAlarm.Cast(extension);
                    if (alarm && house.CanBuyAlarm(alarm)) {
                        name = extension.type;
                    }
                }

                if (name) {
                    extensionListTextWidget.AddItem(name, extension, 0);
                }
            }

            array<ref DZLStorageTypeBought> storages = house.GetStorage();
            foreach(DZLStorageTypeBought storage: storages) {
                sellStorageListTextWidget.AddItem(DZLDisplayHelper.GetItemDisplayName(storage.storageType.type), storage, 0);
            }

			sellStorageListTextWidget.ClearItems();
            array<ref DZLStorageTypeBought> storagesBought = house.GetStorage();
            foreach(DZLStorageTypeBought storageBought: storagesBought) {
                sellStorageListTextWidget.AddItem(DZLDisplayHelper.GetItemDisplayName(storageBought.storageType.type), storage, 0);
            }

            sellButton.Show(false);
			buyButton.Show(false);
        }
	}
}
