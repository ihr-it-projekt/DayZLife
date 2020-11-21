class DZLTraderMenu: DZLBaseMenu
{
	private TextListboxWidget inventory;
	private TextListboxWidget sellCard;
	private TextListboxWidget buyCard;
	private TextListboxWidget traderItemList;
	private TextWidget sum;
	private int sumInt = 0;
	private XComboBoxWidget itemCategory;
	private ButtonWidget tradeButton;
	private TextWidget credits;
	private ItemPreviewWidget preview;
	private DZLTraderPosition position;
	private EntityAI previewItem;
	
	
	private ref map<string, ref array<ref DZLTraderType>> displayCategories;
	
	
    void DZLTraderMenu() {
        layoutPath = "DayZLife/layout/Trader/Trader_Menu.layout";
		displayCategories = new map<string, ref array<ref DZLTraderType>>;
        Construct();
    }

    void ~DZLTraderMenu() {
        Destruct();
    }

    override Widget Init() {
        super.Init();
		
		inventory = creator.GetTextListboxWidget("Inventory");
		sellCard = creator.GetTextListboxWidget("sell_card");
		buyCard = creator.GetTextListboxWidget("buy_card");
		traderItemList = creator.GetTextListboxWidget("Trader_Item_list");
		sum = creator.GetTextWidget("sum");
		sum.SetText("0");

		itemCategory = creator.GetXComboBoxWidget("xcombobox_categorys");
		
		tradeButton = creator.GetButtonWidget("Button_Buy");

		credits = creator.GetTextWidget("Cedits");
		
		preview = creator.GetItemPreviewWidget("previewItem");

        return layoutRoot;
    }

    override void OnShow() {
        super.OnShow();
        sumInt = 0;
		position = player.GetTraderByPosition();

		if (!position) {
		    position = player.GetTraderByPosition();
		}
		
		int index;
		string name = "";
		
		credits.SetText(dzlPlayer.money.ToString());
		
		traderItemList.ClearItems();
		inventory.ClearItems();
		
		array<EntityAI> playerItems = player.GetPlayerItems();
		
        bool hasAddFirstCategory = false;
		
		foreach(string categoryName: position.categoryNames) {
			DZLTraderCategory category = config.traderConfig.categories.GetCatByName(categoryName);
			
			if (!category) continue;
			
			itemCategory.AddItem(categoryName);

			displayCategories.Insert(categoryName, category.items);

			foreach(DZLTraderType type: category.items) {
				name = DZLDisplayHelper.GetItemDisplayName(type.type);
				type.displayName = name;
				if(!hasAddFirstCategory) {
					index = traderItemList.AddItem(name, type, 0);
                    traderItemList.SetItem(index, type.buyPrice.ToString(), type, 1);
                    traderItemList.SetItem(index, type.sellPrice.ToString(), type, 2);
				}
			
				foreach(EntityAI item: playerItems) {
					if (item.GetType() != type.type) {
						continue;
					}
					
					GetGame().ObjectGetDisplayName(item, name);
					
					string quant = item.GetQuantity().ToString();
					
					if (quant == "0") {
						quant = "1";
					}
					
					index = inventory.AddItem(name, item, 0);
					inventory.SetItem(index, type.sellPrice.ToString(), item, 1);
					inventory.SetItem(index, quant, item, 2);
				}


			}
			hasAddFirstCategory = true;
		}
	}
	
	private void SetCategoryItems(string categoryName) {
		traderItemList.ClearItems();

	    ref array<ref DZLTraderType> items = displayCategories.Get(categoryName);
		
		if (items) {
			foreach(DZLTraderType type: items) {
				int index = traderItemList.AddItem(type.displayName, type, 0);
				traderItemList.SetItem(index, type.buyPrice.ToString(), type, 1);
                traderItemList.SetItem(index, type.sellPrice.ToString(), type, 2);
			}
		}
	}

    override bool OnClick(Widget w, int x, int y, int button) {
		
		if (MouseState.MIDDLE == button) {
			if (w == inventory) {
				UpdaterPreviewByEntityAI(inventory);
			} else if (w == sellCard) {
				UpdaterPreviewByEntityAI(sellCard);
			} else if (w == traderItemList) {
				UpdaterPreviewType(traderItemList);
			} else if (w == buyCard) {
				UpdaterPreviewType(buyCard);
			}
		}
		
		
		if (w == tradeButton) {
			array<ref DZLTraderType> buyItems = new array<ref DZLTraderType>;
			array<EntityAI> sellItems = new array<EntityAI>;
			int countBuyItems = buyCard.GetNumItems();
            int countSellItems = sellCard.GetNumItems();

			DZLTraderType buyItem;
			EntityAI sellItem;

			for(x = 0; x < countSellItems; x++) {
                sellItem = null;
                sellCard.GetItemData(x, 0, sellItem);
                if (sellItem) {
                    sellItems.Insert(sellItem);
                }
            }

            for(x = 0; x < countBuyItems; x++) {
                buyItem = null;
                buyCard.GetItemData(x, 0, buyItem);
                if (buyItem) {
                    buyItems.Insert(buyItem);
                }
            }

            if (buyItems.Count() == 0 && sellItems.Count() == 0) {
                return true;
            }

            if (sumInt > player.dzlPlayer.money) {
				player.DisplayMessage("#error_not_enough_money");
				return true;
			}

            GetGame().RPCSingleParam(player, DAY_Z_LIFE_TRADE_ACTION, new Param4<ref array<ref DZLTraderType>, array<EntityAI>, ref DZLTraderPosition, PlayerBase>(buyItems, sellItems, position, player), true);
		} if (w == itemCategory) {
			int categoryIndex = itemCategory.GetCurrentItem();
			string name = position.categoryNames.Get(categoryIndex);
			
			if (name) {
				SetCategoryItems(name);
			}
		}
		
		return true;
    }
	
	override bool OnDoubleClick(Widget w, int x, int y, int button) {
		if (w == inventory) {
			MoveItemFromListWidgetToListWidgetInventory(inventory, sellCard, -1);
		} else if (w == sellCard) {
			MoveItemFromListWidgetToListWidgetInventory(sellCard, inventory, 1);
		} else if (w == traderItemList) {
			MoveItemFromListWidgetToListWidgetTrader(traderItemList, buyCard, false, 1);
		} else if (w == buyCard) {
			MoveItemFromListWidgetToListWidgetTrader(buyCard, traderItemList, true, -1);
		}

		return true;
	}

    override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_TRADE_ACTION_RESPONSE) {
           autoptr Param1<string> paramGetResponse;
           if (ctx.Read(paramGetResponse)){
                UpdateGUI(paramGetResponse.param1);
           }
        }
    }
	
	private void UpdaterPreviewType(TextListboxWidget widget) {
		int pos = widget.GetSelectedRow();
   		if (pos == -1) {
   			return;
   		}
   		DZLTraderType itemType;
   		widget.GetItemData(pos, 0, itemType);

   		if (itemType) {
			EntityAI currentItem = preview.GetItem();
			
			if (currentItem && currentItem.GetType() == itemType.type) return;
	
			if (previewItem) {
	            GetGame().ObjectDelete(previewItem);
	        }
	
	        previewItem = EntityAI.Cast(GetGame().CreateObject(itemType.type, "0 0 0", true, false, false));
	
			preview.SetItem(previewItem);
			preview.SetModelPosition(Vector(0,0,0.5));
		}
	}
	
	private void UpdaterPreviewByEntityAI(TextListboxWidget widget) {
		int pos = widget.GetSelectedRow();
   		if (pos == -1) {
   			return;
   		}
   		EntityAI item;
   		widget.GetItemData(pos, 0, item);

   		if (item) {
			EntityAI currentItem = preview.GetItem();
			
			if (currentItem && currentItem.GetType() == item.GetType()) return;
			
			if (previewItem) {
	            GetGame().ObjectDelete(previewItem);
	        }
	
			preview.SetItem(item);
			preview.SetModelPosition(Vector(0,0,0.5));
	
		}
	}

    private void MoveItemFromListWidgetToListWidgetInventory(TextListboxWidget sourceWidget, TextListboxWidget targetWidget, int factor) {
   		int pos = sourceWidget.GetSelectedRow();
   		if (pos == -1) {
   			return;
   		}
   		EntityAI item;
		DebugMessageDZL("Try get item");
   		sourceWidget.GetItemData(pos, 0, item);
		DebugMessageDZL("has item");
		
   		if (item) {
   		    string name = "";
            sourceWidget.GetItemText(pos, 0, name);
   		    int index;
            index = targetWidget.AddItem(name, item, 0);
            string price = "";
            sourceWidget.GetItemText(pos, 1, price);

            targetWidget.SetItem(index, price, item, 1);
            string quantity = "";
            sourceWidget.GetItemText(pos, 2, quantity);
            targetWidget.SetItem(index, quantity, item, 2);
			sumInt = sumInt + price.ToInt() * factor;
			sum.SetText(sumInt.ToString());
			sourceWidget.RemoveRow(pos);
   		}
   	}
	
	private void MoveItemFromListWidgetToListWidgetTrader(TextListboxWidget sourceWidget, TextListboxWidget targetWidget, bool removeRow, int factor) {
   		int pos = sourceWidget.GetSelectedRow();
   		if (pos == -1) {
   			return;
   		}
   		DZLTraderType itemType;
   		sourceWidget.GetItemData(pos, 0, itemType);

   		if (itemType) {
			string buyPrice = "";
	        sourceWidget.GetItemText(pos, 1, buyPrice);
			
			sumInt = sumInt + buyPrice.ToInt() * factor;
			sum.SetText(sumInt.ToString());
			if (removeRow) {
				DebugMessageDZL("pos" + pos.ToString());
				 sourceWidget.RemoveRow(pos);
			} else {
				string name = "";
	            sourceWidget.GetItemText(pos, 0, name);
	
	   		    int index;
	            index = targetWidget.AddItem(name, itemType, 0);
	            targetWidget.SetItem(index, buyPrice, itemType, 1);
			}
   		}
   	}

}