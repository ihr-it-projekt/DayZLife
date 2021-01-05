class DZLHouseMenu : DZLBaseMenu
{
	
	private XComboBoxWidget selectedPanel;
	private MapWidget mapWidget;
	private TextWidget storageTextWidget;
	private ref DZLHouseDefinition actualHouseDef;
    private ref DZLBuilding house;
    private Building building;
    private ref DZLPreviewWindow preview;
    private ref DZLPreviewWindow upgradePreview;
    private ButtonWidget buyButton;
    private ButtonWidget sellButton;
    private TextWidget priceBuyTextWidget;
    private TextWidget upgardePriceBuyTextWidget;
    private TextWidget priceSellTextWidget;
    private TextWidget upgradePriceSellTextWidget;
    private TextWidget balanceTextWidget;
    private TextListboxWidget extensionListTextWidget;
    private TextListboxWidget sellStorageListTextWidget;
    private TextWidget alarmLevel;
    private MultilineTextWidget upgradeDescription;
	
	private TextListboxWidget keyPlayerList;
	private TextListboxWidget keyPlayerAccessList;
	private ButtonWidget keySaveButton;
	private ButtonWidget searchButton;
	private EditBoxWidget searchInput;
	
	private Widget houseBuy;
	private Widget houseUpgrade;
	private Widget houseKey;
	private int indexPanel;

	private ref array<ref DZLOnlinePlayer> noAccess;

	void DZLHouseMenu(){
	    layoutPath = "DayZLife/layout/Housing/HouseMenu.layout";
        Construct();
	}
	
	void ~DZLHouseMenu(){
        Destruct();
	}

	override Widget Init(){
        super.Init();
		
		selectedPanel = creator.GetXComboBoxWidget("housingComboBox");
		
		houseBuy = creator.GetWidget("housingMenuPanel");
		houseUpgrade = creator.GetWidget("housingUpgradeMenuPanel");
		houseKey = creator.GetWidget("housingKeyMenuPanel");
		
		sellButton = creator.GetButtonWidget("Button_Sell");
        sellButton.Show(false);

        buyButton = creator.GetButtonWidget("Button_Buy");

        preview = new DZLPreviewWindow(creator.GetItemPreviewWidget("Preview"));
        upgradePreview = new DZLPreviewWindow(creator.GetItemPreviewWidget("Preview_UpgradePanel"));

        priceBuyTextWidget = creator.GetTextWidget("Price_Buy");
        upgardePriceBuyTextWidget = creator.GetTextWidget("Price_Buy_UpgradePanel");
        priceSellTextWidget = creator.GetTextWidget("Price_Sell");
        upgradePriceSellTextWidget = creator.GetTextWidget("Price_Sell_UpgradePanel");
        balanceTextWidget = creator.GetTextWidget("Balance");
		
		mapWidget = creator.GetMapWidget("Map");
		mapWidget.SetScale(0.1);
		storageTextWidget = creator.GetTextWidget("Number_of_Storage");

		extensionListTextWidget = creator.GetTextListboxWidget("Storage_List_UpgradePanel");
        sellStorageListTextWidget = creator.GetTextListboxWidget("Sell_Storage_List");
        upgradeDescription = creator.GetMultilineTextWidget("discription_UpgradePanel");
        alarmLevel = creator.GetTextWidget("alarmsystemlvl");
		
		keySaveButton = creator.GetButtonWidget("keySaveButton");
		keyPlayerList = creator.GetTextListboxWidget("keyPlayerList");
		keyPlayerAccessList = creator.GetTextListboxWidget("keyHasKeyList");
		searchButton = creator.GetButtonWidget("searchButton");
		searchInput = creator.GetEditBoxWidget("search_input");

		GetGame().RPCSingleParam(player, DAY_Z_LIFE_HOUSE_ACCESS_LISTS, new Param2<PlayerBase, Building>(player, building), true);

	    return layoutRoot;
    }

	override void OnShow() {
	    extensionListTextWidget.ClearItems();
        sellStorageListTextWidget.ClearItems();
		upgardePriceBuyTextWidget.SetText("");
	    upgradePriceSellTextWidget.SetText("");
		alarmLevel.SetText("0");
		indexPanel = selectedPanel.GetCurrentItem();
	    
		if (actualHouseDef) {
	        super.OnShow();
		   
            balanceTextWidget.SetText(dzlPlayer.GetMoney().ToString());
        
	        priceBuyTextWidget.SetText(actualHouseDef.buyPrice.ToString());
            priceSellTextWidget.SetText(actualHouseDef.sellPrice.ToString());
            storageTextWidget.SetText(actualHouseDef.GetMaxStorage().ToString());
			
			vector mapPos;
			float scale;

			preview.UpdatePreview(actualHouseDef.houseType);
			
			if(player && !player.GetLastMapInfo(scale, mapPos)) {
                mapPos = GetGame().GetCurrentCameraPosition();
			}
			
			houseBuy.Show(true);
			
			selectedPanel.AddItem("#Housing_Menu");	

            buyButton.Show(false);
            sellButton.Show(false);

			if (house && house.HasOwner() && house.IsOwner(player)) {
				selectedPanel.AddItem("#Housing_Upgrade_Menu");
				selectedPanel.AddItem("#Key_Menu");
				if (0 == indexPanel) {
				    buyButton.Show(false);
                    sellButton.Show(true);
				} else {
				    buyButton.Show(true);
                    sellButton.Show(false);
				}
			}


			DZLDisplayHelper.UpdateMap(mapWidget, mapPos);
        }
	}
	
	override bool OnClick(Widget w, int x, int y, int button) {
		if(super.OnClick(w, x, y, button)) return true;
		
		indexPanel = selectedPanel.GetCurrentItem();
		int itemsHasBought = 0;
	
		switch(w){
			case selectedPanel: 
                houseBuy.Show(0 == indexPanel);
                sellButton.Show(0 == indexPanel && house.HasOwner() && house.IsOwner(player));
                buyButton.Show(0 == indexPanel && (!house.HasOwner() || !house.IsOwner(player)));
                houseUpgrade.Show(1 == indexPanel);
                houseKey.Show(2 == indexPanel);
							
				return true;
            case buyButton:
                if (0 == indexPanel) {
                    if (actualHouseDef) {
                        if (dzlPlayer.HasEnoughMoney(actualHouseDef.buyPrice)) {
                            Param2<PlayerBase, ref Building> paramBuyHouse = new Param2<PlayerBase, ref Building>(player, building);
                            GetGame().RPCSingleParam(paramBuyHouse.param1, DAY_Z_LIFE_OPEN_BUY_BUILDING, paramBuyHouse, true);
                        } else {
                            player.DisplayMessage("#error_not_enough_money");
                        }
                    } else {
                        player.DisplayMessage("#error_please_reopen_menu");
                    }
				} else if (1 == indexPanel) {
				    int itemPosBuy = extensionListTextWidget.GetSelectedRow();
                    DZLHouseExtension currentItemBuy;
                    extensionListTextWidget.GetItemData(itemPosBuy, 0, currentItemBuy);

                    if (!currentItemBuy) {
                        return true;
                    }

                    int buyPriceBuy = 0;
                    bool canBuy = false;

                    if (currentItemBuy.isStorage) {
						itemsHasBought = sellStorageListTextWidget.GetNumItems() + 1;
                        buyPriceBuy =  currentItemBuy.price * (actualHouseDef.storageBuyFactor * (itemsHasBought + 1));
                        canBuy = actualHouseDef.GetMaxStorage() > sellStorageListTextWidget.GetNumItems();
                    } else {
                        buyPriceBuy = currentItemBuy.price;
                        canBuy = dzlPlayer.HasEnoughMoney(buyPriceBuy) && house.IsOwner(player) && house.CanBuyAlarm(currentItemBuy);
                    }

                    if (canBuy) {
                        GetGame().RPCSingleParam(player, DAY_Z_LIFE_BUY_EXTENSION, new Param3<PlayerBase, ref Building, string>(player, building, currentItemBuy.id), true);
                    }
				}
                return true;
            case sellButton:
                if (0 == indexPanel && house && house.HasOwner() && house.IsOwner(player)) {
                    Param2<PlayerBase, ref Building> paramSellHouse = new Param2<PlayerBase, ref Building>(player, building);
                    GetGame().RPCSingleParam(paramSellHouse.param1, DAY_Z_LIFE_OPEN_SELL_BUILDING, paramSellHouse, true);
                } else if (1 == indexPanel) {
                    int itemPosStorageSell = sellStorageListTextWidget.GetSelectedRow();
                    DZLStorageTypeBought currentItemStorageSell;
                    sellStorageListTextWidget.GetItemData(itemPosStorageSell, 0, currentItemStorageSell);

                    if (!currentItemStorageSell) return true;

                    PlayerBase playerBaseSell = player;
                    if (house.IsOwner(playerBaseSell)) {
                        GetGame().RPCSingleParam(playerBaseSell, DAY_Z_LIFE_SELL_STORAGE, new Param3<PlayerBase, ref Building, vector>(playerBaseSell, building, currentItemStorageSell.position), true);
                    }
                }
                return true;
            case extensionListTextWidget:
                int itemPos = extensionListTextWidget.GetSelectedRow();

                if (-1 == itemPos) return true;

                DZLHouseExtension currentItem;
                extensionListTextWidget.GetItemData(itemPos, 0, currentItem);

                if (!currentItem) return true;

                int buyPrice = currentItem.price;
                int sellPrice = 0;
                bool showBuyButton = true;

                upgradeDescription.SetText(currentItem.description);

                if (currentItem.isStorage) {
                    itemsHasBought = sellStorageListTextWidget.GetNumItems() + 1;

                    upgradePreview.UpdatePreview(currentItem.type);

                    buyPrice =  currentItem.price * (actualHouseDef.storageBuyFactor * itemsHasBought);

                    sellPrice =  buyPrice / 2;

                    sellButton.Show(false);
                    showBuyButton = actualHouseDef.GetMaxStorage() > house.GetStorage().Count();

                    if (actualHouseDef.GetMaxStorage() <= house.GetStorage().Count()) {
                        player.DisplayMessage("#building_has_all_storrage_positions_upgraded");
                    }
                }

                upgardePriceBuyTextWidget.SetText(buyPrice.ToString());
                upgradePriceSellTextWidget.SetText(sellPrice.ToString());
                buyButton.Show(showBuyButton);

                return true;
            case sellStorageListTextWidget:

                int itemPosSell = sellStorageListTextWidget.GetSelectedRow();

                if (-1 == itemPosSell) return true;

                DZLStorageTypeBought currentItemSell;
                sellStorageListTextWidget.GetItemData(itemPosSell, 0, currentItemSell);

                if (!currentItemSell) return true;

                upgradePreview.UpdatePreview(currentItemSell.type);

                upgardePriceBuyTextWidget.SetText(currentItemSell.paidPrice.ToString());
                upgradePriceSellTextWidget.SetText(currentItemSell.sellPrice.ToString());

                buyButton.Show(false);
                sellButton.Show(true);

                return true;
            case keySaveButton:
                GetGame().RPCSingleParam(player, DAY_Z_LIFE_HOUSE_ACCESS_LISTS_SAVE, new Param3<PlayerBase, Building, ref array<string>>(player, building, DZLDisplayHelper.GetPlayerIdsFromList(keyPlayerAccessList)), true);
                searchInput.SetText("");
                return true;
			case searchButton:
				DZLDisplayHelper.SearchOnlinePlayers(searchInput.GetText(), keyPlayerList, keyPlayerAccessList, noAccess, player);
				return true;
            default:
                break;
		}
		return false;
	}
	
	override bool OnDoubleClick(Widget w, int x, int y, int button) {
        if (w == keyPlayerList) {
            DZLDisplayHelper.MoveDZLOnlinePlayerFromListWidgetToListWidget(keyPlayerList, keyPlayerAccessList);
        } else if (w == keyPlayerAccessList) {
            DZLDisplayHelper.MoveDZLOnlinePlayerFromListWidgetToListWidget(keyPlayerAccessList, keyPlayerList);
        }

        return false;
    }

	override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
	    super.HandleEventsDZL(sender, target, rpc_type, ctx);
        if (rpc_type == DAY_Z_LIFE_OPEN_BUY_BUILDING_RESPONSE || rpc_type == DAY_Z_LIFE_OPEN_SELL_BUILDING_RESPONSE) {
            autoptr Param2<ref DZLBuilding, string> paramBuyHouse;
            if (ctx.Read(paramBuyHouse)){
                GetGame().RPCSingleParam(player, DAY_Z_LIFE_HOUSE_ACCESS_LISTS, new Param2<PlayerBase, Building>(player, building), true);
				house = paramBuyHouse.param1;
				UpdateGUI(paramBuyHouse.param2);
	        }
        } else if (rpc_type == DAY_Z_LIFE_OPEN_GET_BUILDING_DATA_RESPONSE) {
            autoptr Param1<ref DZLBuilding> paramGetBuildingProperties;
            if (ctx.Read(paramGetBuildingProperties)){
                house = paramGetBuildingProperties.param1;
                UpdateGUI();
            }
        } else if (rpc_type == DAY_Z_LIFE_BUY_EXTENSION_RESPONSE || rpc_type == DAY_Z_LIFE_SELL_STORAGE_RESPONSE) {
            autoptr Param2<ref DZLBuilding, string> paramBuyStorageResponse;
            if (ctx.Read(paramBuyStorageResponse)){
                house = paramBuyStorageResponse.param1;

                UpdateGUI(paramBuyStorageResponse.param2);
            }
        } else if (rpc_type == DAY_Z_LIFE_HOUSE_ACCESS_LISTS_RESPONSE) {
            autoptr Param2<ref array<ref DZLOnlinePlayer>, ref array<ref DZLOnlinePlayer>> paramPlayers;
            if (ctx.Read(paramPlayers)){
                noAccess = paramPlayers.param2;
                array<ref DZLOnlinePlayer> access = paramPlayers.param1;
				keyPlayerList.ClearItems();
				keyPlayerAccessList.ClearItems();
                foreach(DZLOnlinePlayer playerNoAccess: noAccess) {
					keyPlayerList.AddItem(playerNoAccess.name, playerNoAccess, 0);
				}
				
				foreach(DZLOnlinePlayer playerAccess: access) {
					keyPlayerAccessList.AddItem(playerAccess.name, playerAccess, 0);
				}
            }
        }
    }
	
	override void UpdateGUI(string message = "") {
	    super.UpdateGUI(message);
		
		balanceTextWidget.SetText(dzlPlayer.GetMoney().ToString());
		
		if (indexPanel == 0 && house && house.HasOwner() && house.IsOwner(player)) {
			sellButton.Show(true);
			buyButton.Show(false);
			
		} else if (indexPanel == 0 && house && house.HasOwner() && !house.IsOwner(player)) {
			sellButton.Show(false);
			buyButton.Show(false);
			player.DisplayMessage("#building_has_already_an_owner");
			
		} else if (indexPanel == 0 && house && !house.HasOwner()) {
			sellButton.Show(false);
			buyButton.Show(true);
			
		} else if (indexPanel == 0 && !house) {
			sellButton.Show(false);
			buyButton.Show(false);
		} 
		
		if (house) {
			if (house.HasOwner() && house.IsOwner(player) && selectedPanel.GetNumItems() == 1) {
				selectedPanel.AddItem("#Housing_Upgrade_Menu");
				selectedPanel.AddItem("#Key_Menu");
			} else if(selectedPanel.GetNumItems() > 1 && (!house.HasOwner() || house.IsOwner(player))) {
				selectedPanel.RemoveItem(2);
				selectedPanel.RemoveItem(1);
			}
			
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
        }
		
		if (indexPanel == 1) {
			sellButton.Show(false);
            buyButton.Show(false);
		}
	}
	
	 void SetTarget(Building building) {
        this.building = building;
        Param2<PlayerBase,ref Building> paramGetBuildingProperties = new Param2<PlayerBase,ref Building>(player, this.building);
        GetGame().RPCSingleParam(paramGetBuildingProperties.param1, DAY_Z_LIFE_OPEN_GET_BUILDING_DATA, paramGetBuildingProperties, true);
    }

	void SetHouseDefinition(DZLHouseDefinition definition) {
		actualHouseDef = definition;
	}

}
