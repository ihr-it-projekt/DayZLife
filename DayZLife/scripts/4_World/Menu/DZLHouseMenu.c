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
	
	private TextListboxWidget playerInventoryList;
	private TextListboxWidget playerInventoryAddList;
	private TextListboxWidget houseInventoryList;
	private TextListboxWidget houseInventoryAddList;
	private ItemPreviewWidget inventoryPreview;
	private ButtonWidget transferButton;
	private TextWidget storagelvlCount;
	private TextWidget storageItemCountMax;
	private TextWidget totalStorageSpace;
	private TextWidget storageSpaceAvailable;
	
	private Widget houseBuy;
	private Widget houseUpgrade;
	private Widget houseKey;
	private Widget houseInventoryWidget;

	private int indexHouseBuy = -1;
	private int indexHouseUpgrade = -1;
	private int indexHouseKey = -1;
	private int indexHouseInventor = -1;
	
	private ref array<ref DZLOnlinePlayer> noAccess;
	private ref DZLHouseInventory inventory;

	private int lastSelectedPlayerInventory;
	private int lastSelectedPlayerAddInventory;
	private int lastSelectedHouseInventory;
	private int lastSelectedHouseAddInventory;

	void DZLHouseMenu(){
	    layoutPath = "DayZLife/layout/Housing/HouseMenu.layout";
        Construct();
	}
	
	void ~DZLHouseMenu(){
	    DZLDisplayHelper.DeletePreviewItem();
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
		
		playerInventoryList = creator.GetTextListboxWidget("inventoryListbox");
		playerInventoryAddList = creator.GetTextListboxWidget("inventoryAddListbox");
		houseInventoryList = creator.GetTextListboxWidget("houseStorageListbox");
		houseInventoryAddList = creator.GetTextListboxWidget("houseStorageAddListbox");
		transferButton = creator.GetButtonWidget("transferButton");
		inventoryPreview = creator.GetItemPreviewWidget("houseStoragePreview");
		storageItemCountMax = creator.GetTextWidget("storageItemCountMax");
		storagelvlCount = creator.GetTextWidget("storagelvlCount");
		totalStorageSpace = creator.GetTextWidget("totalStorageSpace");
		storageSpaceAvailable = creator.GetTextWidget("storageSpaceAvailable");
		
		houseInventoryWidget = creator.GetWidget("housingStorageMenuPanel");

		GetGame().RPCSingleParam(player, DAY_Z_LIFE_HOUSE_ACCESS_LISTS, new Param1<Building>(building), true);

	    return layoutRoot;
    }

	override void OnShow() {
	    extensionListTextWidget.ClearItems();
        sellStorageListTextWidget.ClearItems();
		upgardePriceBuyTextWidget.SetText("");
	    upgradePriceSellTextWidget.SetText("");
		alarmLevel.SetText("0");
		int maxSpace = config.houseExtensions.maxHouseInventoryLevel * config.houseExtensions.inventoryItemsPerLevel;
		storageItemCountMax.SetText(maxSpace.ToString());
		storagelvlCount.SetText("0");

		storageSpaceAvailable.SetText("0");
	    
		if (actualHouseDef) {
	        super.OnShow();

	        priceBuyTextWidget.SetText(actualHouseDef.buyPrice.ToString());
            priceSellTextWidget.SetText(actualHouseDef.sellPrice.ToString());
            storageTextWidget.SetText(actualHouseDef.GetMaxStorage().ToString());

			vector mapPos;
			float scale;
			preview.UpdatePreview(actualHouseDef.houseType);
			
			if(player && !player.GetLastMapInfo(scale, mapPos)) {
                mapPos = GetGame().GetCurrentCameraPosition();
			}

			selectedPanel.AddItem("#Housing_Menu");
			indexHouseBuy = selectedPanel.GetNumItems() - 1;
			houseBuy.Show(true);

			DZLDisplayHelper.UpdateMap(mapWidget, mapPos);
            UpdateGUI();
        }
	}
	
	override bool OnClick(Widget w, int x, int y, int button) {
		if(super.OnClick(w, x, y, button)) return true;
		int itemsHasBought = 0;
		int indexPanel = -1;
		switch(w){
			case selectedPanel:
			    indexPanel = selectedPanel.GetCurrentItem();
				houseInventoryWidget.Show(indexHouseInventor == indexPanel);
				houseBuy.Show(indexHouseBuy == indexPanel);
                houseUpgrade.Show(indexHouseUpgrade == indexPanel);
                houseKey.Show(indexHouseKey == indexPanel);
                sellButton.Show(indexHouseBuy == indexPanel && house.HasOwner() && house.IsOwner(player));
                buyButton.Show(indexHouseBuy == indexPanel && !house.HasOwner());

				return true;
            case buyButton:
                indexPanel = selectedPanel.GetCurrentItem();
                if (indexHouseBuy == indexPanel) {
                    if (actualHouseDef) {
                        if (dzlPlayer.HasEnoughMoney(actualHouseDef.buyPrice)) {
                            GetGame().RPCSingleParam(player, DAY_Z_LIFE_OPEN_BUY_BUILDING, new Param1<Building>(building), true);
                        } else {
                            player.DisplayMessage("#error_not_enough_money");
                        }
                    } else {
                        player.DisplayMessage("#error_please_reopen_menu");
                    }
				} else if (indexHouseUpgrade == indexPanel) {
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
                    } else if(currentItemBuy.isHouseInventory) {
                        int currentLevel = 0;
                        float factor = 1.0;

                        if (inventory) {
                            currentLevel = inventory.GetLevel(config.houseExtensions.inventoryItemsPerLevel);

                            factor = currentLevel * 10 / 100 + 1;
                        }

                        buyPriceBuy = config.houseExtensions.pricePerLevelHouseInventory * factor;
                        canBuy = dzlPlayer.HasEnoughMoney(buyPriceBuy) && house.IsOwner(player) && house.CanBuyInventoryExtensionClient(config.houseExtensions, inventory);
                    } else {
                        buyPriceBuy = currentItemBuy.price;
                        canBuy = dzlPlayer.HasEnoughMoney(buyPriceBuy) && house.IsOwner(player) && house.CanBuyAlarm(currentItemBuy);
                    }

                    if (canBuy) {
                        GetGame().RPCSingleParam(player, DAY_Z_LIFE_BUY_EXTENSION, new Param2<Building, string>(building, currentItemBuy.GetId()), true);
                    }

                    buyButton.Show(false);
				}
                return true;
            case sellButton:
                indexPanel = selectedPanel.GetCurrentItem();
                if (indexHouseBuy == indexPanel && house && house.HasOwner() && house.IsOwner(player)) {
                    GetGame().RPCSingleParam(player, DAY_Z_LIFE_OPEN_SELL_BUILDING, new Param1<Building>(building), true);
                } else if (indexHouseUpgrade == indexPanel) {
                    int itemPosStorageSell = sellStorageListTextWidget.GetSelectedRow();
                    DZLStorageTypeBought currentItemStorageSell;
                    sellStorageListTextWidget.GetItemData(itemPosStorageSell, 0, currentItemStorageSell);

                    if (!currentItemStorageSell) return true;

                    PlayerBase playerBaseSell = player;
                    if (house.IsOwner(playerBaseSell)) {
                        GetGame().RPCSingleParam(playerBaseSell, DAY_Z_LIFE_SELL_STORAGE, new Param2<Building, vector>(building, currentItemStorageSell.position), true);
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
                } else if (currentItem.isHouseInventory) {

                    showBuyButton = house.CanBuyInventoryExtensionClient(config.houseExtensions, inventory);
                    sellButton.Show(false);

                    int currentLevelUpgrade = 0;
                    float factorUpgrade = 1.0;

                    if (inventory) {
                        currentLevelUpgrade = inventory.GetLevel(config.houseExtensions.inventoryItemsPerLevel);
                        factorUpgrade = currentLevelUpgrade * 10 / 100 + 1;
                    }

                    buyPrice = config.houseExtensions.pricePerLevelHouseInventory * factorUpgrade;
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
                GetGame().RPCSingleParam(player, DAY_Z_LIFE_HOUSE_ACCESS_LISTS_SAVE, new Param2<Building, ref array<DZLOnlinePlayer>>(building, DZLDisplayHelper.GetPlayerIdsAndRanksFromList(keyPlayerAccessList)), true);
                searchInput.SetText("");
                return true;
			case searchButton:
				DZLDisplayHelper.SearchOnlinePlayersWithKey(searchInput.GetText(), keyPlayerList, keyPlayerAccessList, noAccess, player);
				return true;
		    case transferButton:
		        array<string> storeOutItems = new array<string>;
                int countStoreOutItems = playerInventoryAddList.GetNumItems();
                array<EntityAI> storeInItems = new array<EntityAI>;
                int countStoreInItems = houseInventoryAddList.GetNumItems();

                DZLStoreItem outItem;
                EntityAI inItem;
                int z;

                for(z = 0; z < countStoreOutItems; z++) {
                    outItem = null;
                    playerInventoryAddList.GetItemData(z, 0, outItem);

					if (!outItem) continue;
                    storeOutItems.Insert(outItem.GetId());
                }


                for(z = 0; z < countStoreInItems; z++) {
                    inItem = null;
                    houseInventoryAddList.GetItemData(z, 0, inItem);
					
					if (!inItem) continue;
                    storeInItems.Insert(inItem);
                }

                if (storeOutItems.Count() == 0 && storeInItems.Count() == 0) {
                    return true;
                }

                GetGame().RPCSingleParam(player, DAY_Z_LIFE_HOUSE_STORE_ITEMS, new Param4<string, vector, ref array<string>, ref array<EntityAI>>(house.GetDZLHouse().GetOwner(), building.GetPosition(), storeOutItems, storeInItems), true);

		        return true;
            default:
                break;
		}
		return false;
	}
	
	override bool OnDoubleClick(Widget w, int x, int y, int button) {
        if (w == keyPlayerList) {
            DZLDisplayHelper.MoveDZLOnlinePlayerFromListWidgetToListWidget(keyPlayerList, keyPlayerAccessList, DAY_Z_LIFE_JOB_CIVIL);
        } else if (w == keyPlayerAccessList) {
            DZLDisplayHelper.MoveDZLOnlinePlayerFromListWidgetToListWidget(keyPlayerAccessList, keyPlayerList, DAY_Z_LIFE_JOB_CIVIL);
        } else if (w == houseInventoryList) {
            DZLDisplayHelper.MoveStoreItemFromListWidgetToListWidget(houseInventoryList, playerInventoryAddList);
        } else if (w == houseInventoryAddList) {
            DZLDisplayHelper.MoveItemFromListWidgetToListWidget(houseInventoryAddList, playerInventoryList);
        } else if (w == playerInventoryList) {
            DZLDisplayHelper.MoveItemFromListWidgetToListWidget(playerInventoryList, houseInventoryAddList);
        } else if (w == playerInventoryAddList) {
            DZLDisplayHelper.MoveStoreItemFromListWidgetToListWidget(playerInventoryAddList, houseInventoryList);
        }

        return false;
    }

    override void Update(float timeslice) {
        super.Update(timeslice);
        int currentSelectedPlayerInventory = playerInventoryList.GetSelectedRow();
        int currentSelectedPlayerAddInventory = playerInventoryAddList.GetSelectedRow();
        int currentSelectedHouseInventory = houseInventoryList.GetSelectedRow();
        int currentSelectedHouseAddInventory = houseInventoryAddList.GetSelectedRow();

        if (currentSelectedPlayerInventory != lastSelectedPlayerInventory) {
            DZLDisplayHelper.UpdaterPreviewByEntityAI(playerInventoryList, inventoryPreview);
            lastSelectedPlayerInventory = currentSelectedPlayerInventory;
        } else if (currentSelectedPlayerAddInventory != lastSelectedPlayerAddInventory) {
            DZLDisplayHelper.UpdaterPreviewByStoreItem(playerInventoryAddList, inventoryPreview);
            lastSelectedPlayerAddInventory = currentSelectedPlayerAddInventory;
        } else if (currentSelectedHouseInventory != lastSelectedHouseInventory) {
            DZLDisplayHelper.UpdaterPreviewByStoreItem(houseInventoryList, inventoryPreview);
            lastSelectedHouseInventory = currentSelectedHouseInventory;
        } else if (currentSelectedHouseAddInventory != lastSelectedHouseAddInventory) {
            DZLDisplayHelper.UpdaterPreviewByEntityAI(houseInventoryAddList, inventoryPreview);
            lastSelectedHouseAddInventory = currentSelectedHouseAddInventory;
        }
    }

	override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
	    super.HandleEventsDZL(sender, target, rpc_type, ctx);
        if (rpc_type == DAY_Z_LIFE_OPEN_BUY_BUILDING_RESPONSE || rpc_type == DAY_Z_LIFE_OPEN_SELL_BUILDING_RESPONSE) {
            autoptr Param2<ref DZLBuilding, string> paramBuyHouse;
            if (ctx.Read(paramBuyHouse)){
                GetGame().RPCSingleParam(player, DAY_Z_LIFE_HOUSE_ACCESS_LISTS, new Param1<Building>(building), true);
				house = paramBuyHouse.param1;
				UpdateGUI(paramBuyHouse.param2);
	        }
        } else if (rpc_type == DAY_Z_LIFE_OPEN_GET_BUILDING_DATA_RESPONSE) {
            autoptr Param1<ref DZLBuilding> paramGetBuildingProperties;
            if (ctx.Read(paramGetBuildingProperties)){
                house = paramGetBuildingProperties.param1;
				
				if (house && house.HasInventory()) {
					GetGame().RPCSingleParam(null, DAY_Z_LIFE_OPEN_GET_BUILDING_INVENTORY_DATA, new Param2<string, vector>(house.GetDZLHouse().GetOwner(), this.building.GetPosition()), true);
				}
				
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
				UpdateGUI();
            }
        } else if (rpc_type == DAY_Z_LIFE_OPEN_GET_BUILDING_INVENTORY_DATA_RESPONSE) {
			autoptr Param1<ref DZLHouseInventory> paramInventoryResponse;
			if (ctx.Read(paramInventoryResponse)) {
				inventory = paramInventoryResponse.param1;

				houseInventoryList.ClearItems();
				houseInventoryAddList.ClearItems();
				playerInventoryList.ClearItems();
				playerInventoryAddList.ClearItems();

				array<EntityAI> playerItems = player.GetPlayerItems();
				array<ref DZLStoreItem> houseInventoryItems = inventory.GetStore();
				
				foreach(DZLStoreItem storeItem: houseInventoryItems) {
					houseInventoryList.AddItem(DZLDisplayHelper.GetItemDisplayName(storeItem.type), storeItem, 0);
				}

				foreach(EntityAI playerItem: playerItems) {
					GameInventory itemInventory = playerItem.GetInventory();
					CargoBase cargo = itemInventory.GetCargo();
					if (cargo && cargo.GetItemCount() > 0 || player == playerItem || itemInventory.IsAttachment()) {
					    continue;
					}
                    string name = "";
                    GetGame().ObjectGetDisplayName(playerItem, name);

					playerInventoryList.AddItem(name, playerItem, 0);
				}

				UpdateGUI();
			}
		}
    }
	
	override void UpdateGUI(string message = "") {
	    super.UpdateGUI(message);

		if (house) {
		    if (house.HasOwner() && house.IsOwner(player)) {
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
                    } else if(extension.isHouseInventory && house.CanBuyInventoryExtensionClient(config.houseExtensions, inventory)) {
                        name = "#House_Storage";
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

		        if (indexHouseUpgrade == -1) {
		            selectedPanel.AddItem("#Housing_Upgrade_Menu");
                    indexHouseUpgrade = selectedPanel.GetNumItems() - 1;
		        }
                if (indexHouseKey == -1){
                    selectedPanel.AddItem("#Key_Menu");
                    indexHouseKey = selectedPanel.GetNumItems() - 1;
                }
                if (indexHouseInventor == -1 && house.HasInventory() && inventory) {
                    selectedPanel.AddItem("#House_Storage");
                    indexHouseInventor = selectedPanel.GetNumItems() - 1;
                } else if(indexHouseInventor == -1 && house.HasInventory() && !inventory) {
                    GetGame().RPCSingleParam(null, DAY_Z_LIFE_OPEN_GET_BUILDING_INVENTORY_DATA, new Param2<string, vector>(house.GetDZLHouse().GetOwner(), building.GetPosition()), true);
                }
		    } else if (house.HasOwner() && !house.IsOwner(player)) {
		        if (indexHouseInventor == -1 && (!house.HasLockedDoors() || house.HasPlayerAccess(dzlPlayer.dayZPlayerId) || (config.adminIds.CanManageCops(dzlPlayer.dayZPlayerId) && dzlPlayer.IsActiveAsCop())) && house.HasInventory() && inventory) {
                    selectedPanel.AddItem("#House_Storage");
                    indexHouseInventor = selectedPanel.GetNumItems() - 1;
                } else if (indexHouseInventor != -1) {
				    selectedPanel.RemoveItem(indexHouseInventor);
				    indexHouseInventor = -1;
			    }

			    if (indexHouseKey != -1) {
				    selectedPanel.RemoveItem(indexHouseKey);
				    indexHouseKey = -1;
			    }

			    if (indexHouseUpgrade != -1) {
				    selectedPanel.RemoveItem(indexHouseUpgrade);
				    indexHouseUpgrade = -1;
			    }

			    if (dzlPlayer.IsActiveAsCop()) {
			        player.DisplayMessage("#owner_is: " + house.GetOwnerName());
			    } else {
			        player.DisplayMessage("#building_has_alrready_an_owner");
			    }
			}
        }

		balanceTextWidget.SetText(dzlPlayer.GetMoney().ToString());

		if (inventory) {
		    storagelvlCount.SetText(inventory.GetLevel(config.houseExtensions.inventoryItemsPerLevel).ToString());
		    upgardePriceBuyTextWidget.SetText("");
            storageSpaceAvailable.SetText(inventory.GetLeftStorage().ToString());
		}

        int indexPanel = selectedPanel.GetCurrentItem();

        if (indexPanel == indexHouseBuy && house && house.HasOwner() && house.IsOwner(player)) {
            sellButton.Show(true);
            buyButton.Show(false);

        } else if (indexPanel == indexHouseBuy && house && house.HasOwner() && !house.IsOwner(player)) {
            sellButton.Show(false);
            buyButton.Show(false);
        } else if (indexPanel == indexHouseBuy && house && !house.HasOwner()) {
            sellButton.Show(false);
            buyButton.Show(true);
        } else if (indexPanel == indexHouseBuy && !house) {
            sellButton.Show(false);
            buyButton.Show(false);
        }
	}
	
	 void SetTarget(Building building) {
        this.building = building;
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_OPEN_GET_BUILDING_DATA, new Param1<Building>(this.building), true);
    }

	void SetHouseDefinition(DZLHouseDefinition definition) {
		actualHouseDef = definition;
	}

}
