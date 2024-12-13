class DZLTraderMenu: DZLBaseMenu {
    private TextListboxWidget inventory;
    private TextListboxWidget sellCard;
    private TextListboxWidget buyCard;
    private TextListboxWidget traderItemList;
    private TextWidget sum;
    private int sumInt = 0;
    private int taxInt = 0;
    private XComboBoxWidget itemCategory;
    private ButtonWidget tradeButton;
    private TextWidget credits;
    private TextWidget tax;
    private ItemPreviewWidget preview;
    private ref DZLTraderPosition position;

    private int lastSelectedInventory;
    private int lastSelectedSellCard;
    private int lastSelectedBuyCard;
    private int lastSelectedTraderItemList;

    private ref map<string, ref array<ref DZLTraderType>> displayCategories;
    private ref array<string> addedCats;
    private ref array<ref DZLTraderTypeStorage> storageOfItems;


    void DZLTraderMenu(ref DZLTraderPosition _position) {
        position = _position;
        layoutPath = "DayZLifeClient/layout/Trader/Trader_Menu.layout";
        displayCategories = new map<string, ref array<ref DZLTraderType>>;
        addedCats = new array<string>;

        showHud = false;
        showQuickBar = false;
    }

    void ~DZLTraderMenu() {
        DZLDisplayHelper.DeletePreviewItem();
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
        tax = creator.GetTextWidget("tax");
        tax.SetText("0");

        preview = creator.GetItemPreviewWidget("previewItem");

        g_Game.RPCSingleParam(player, DZL_RPC.EVENT_GET_CONFIG_TRADER_STORAGE, null, true);

        return layoutRoot;
    }

    override void UpdateGUI(string message = "") {
        super.UpdateGUI(message);

        array<EntityAI> playerItems = player.GetPlayerItems();
        credits.SetText(dzlPlayer.GetMoney().ToString());

        inventory.ClearItems();
        sellCard.ClearItems();
        buyCard.ClearItems();
        sumInt = 0;
        taxInt = 0;
        UpdateSum();
        string name = "";
        int index;
        string quant;

        array<string> addInventoryTypes = new array<string>;

        foreach(string categoryName: position.categoryNames) {
            DZLTraderCategory category = config.traderConfig.categories.GetCatByName(categoryName);

            if(!category) continue;

            foreach(DZLTraderType type: category.items) {
                if(type.sellPrice <= 0) continue;
                if(-1 != addInventoryTypes.Find(type.type)) continue;

                DZLTraderTypeStorage storage = GetCurrentStorageByName(type.type);

                int price = type.CalculateDynamicSellPrice(storage);
                price = DZLTraderHelper.GetQuantityPrice(price);

                addInventoryTypes.Insert(type.type);

                if(type.isCar) {
                    CarScript playerCar = DZLObjectFinder.GetCar(position.spawnPositionOfVehicles, position.spawnOrientationOfVehicles, type.type, dzlPlayer, true);

                    if(playerCar && !playerCar.isSold) {
                        quant = DZLTraderHelper.GetQuantity(playerCar).ToString();

                        g_Game.ObjectGetDisplayName(playerCar, name);
                        index = inventory.AddItem(name, playerCar, 0);
                        inventory.SetItem(index, price.ToString(), type, 1);
                        inventory.SetItem(index, quant, playerCar, 2);
                        inventory.SetItem(index, type.GetStorageString(storage), playerCar, 3);
                    }
                    continue;
                }

                foreach(EntityAI item: playerItems) {
                    if(item.GetType() != type.type) continue;

                    g_Game.ObjectGetDisplayName(item, name);

                    quant = DZLTraderHelper.GetQuantity(item).ToString();
                    price = DZLTraderHelper.GetQuantityPrice(price, item);

                    index = inventory.AddItem(name, item, 0);
                    inventory.SetItem(index, price.ToString(), type, 1);
                    inventory.SetItem(index, quant, item, 2);
                    inventory.SetItem(index, type.GetStorageString(storage), item, 3);
                }
            }
        }
    }

    void RenderView() {
        sumInt = 0;
        taxInt = 0;

        int index;
        string name = "";
        int quantity;

        credits.SetText(dzlPlayer.GetMoney().ToString());

        traderItemList.ClearItems();
        inventory.ClearItems();

        array<EntityAI> playerItems = player.GetPlayerItems();

        bool hasAddFirstCategory = false;

        array<string> addInventoryTypes = new array<string>;

        foreach(string categoryName: position.categoryNames) {
            DZLTraderCategory category = config.traderConfig.categories.GetCatByName(categoryName);
            if(!category) continue;
            if(displayCategories.Get(category.name)) continue;

            itemCategory.AddItem(categoryName);
            displayCategories.Insert(categoryName, category.items);
            addedCats.Insert(categoryName);

            foreach(DZLTraderType type: category.items) {
                DZLTraderTypeStorage storage = GetCurrentStorageByName(type.type);
                name = DZLDisplayHelper.GetItemDisplayName(type.type);
                type.displayName = name;
                int sellPrice = type.CalculateDynamicSellPrice(storage);
                sellPrice = DZLTraderHelper.GetQuantityPrice(sellPrice);
                if(!hasAddFirstCategory) {
                    index = traderItemList.AddItem(name, type, 0);

                    int buyPrice = type.CalculateDynamicBuyPrice(storage);

                    traderItemList.SetItem(index, buyPrice.ToString(), type, 1);
                    traderItemList.SetItem(index, sellPrice.ToString(), type, 2);
                    traderItemList.SetItem(index, type.GetStorageString(storage), type, 3);
                }

                if(-1 != addInventoryTypes.Find(type.type)) continue;

                addInventoryTypes.Insert(type.type);

                if(type.sellPrice <= 0) continue

                    if(type.isCar) {
                        CarScript playerCar = DZLObjectFinder.GetCar(position.spawnPositionOfVehicles, position.spawnOrientationOfVehicles, type.type, dzlPlayer, true);

                        if(playerCar && !playerCar.isSold) {
                            g_Game.ObjectGetDisplayName(playerCar, name);
                            index = inventory.AddItem(name, playerCar, 0);
                            inventory.SetItem(index, sellPrice.ToString(), type, 1);
                            inventory.SetItem(index, "1", playerCar, 2);
                            inventory.SetItem(index, type.GetStorageString(storage), playerCar, 3);
                        }
                        continue;
                    }

                foreach(EntityAI item: playerItems) {
                    if(item.GetType() != type.type) {
                        continue;
                    }

                    g_Game.ObjectGetDisplayName(item, name);
                    int sumItem = type.CalculateDynamicSellPrice(storage);
                    sumItem = DZLTraderHelper.GetQuantityPrice(sumItem, item);
                    quantity = DZLTraderHelper.GetQuantity(item);

                    index = inventory.AddItem(name, item, 0);
                    inventory.SetItem(index, sumItem.ToString(), type, 1);
                    inventory.SetItem(index, quantity.ToString(), item, 2);
                    inventory.SetItem(index, type.GetStorageString(storage), item, 3);
                }
            }
            hasAddFirstCategory = true;
        }
    }

    override void Update(float timeslice) {
        super.Update(timeslice);
        int currentSelectedInventory = inventory.GetSelectedRow();
        int currentSelectedSellCard = sellCard.GetSelectedRow();
        int currentSelectedBuyCard = buyCard.GetSelectedRow();
        int currentSelectedTraderItemList = traderItemList.GetSelectedRow();

        if(currentSelectedInventory != lastSelectedInventory) {
            DZLDisplayHelper.UpdaterPreviewByEntityAI(inventory, preview);
            lastSelectedInventory = currentSelectedInventory;
        } else if(currentSelectedSellCard != lastSelectedSellCard) {
            DZLDisplayHelper.UpdaterPreviewByEntityAI(sellCard, preview);
            lastSelectedSellCard = currentSelectedSellCard;
        } else if(currentSelectedTraderItemList != lastSelectedTraderItemList) {
            DZLDisplayHelper.UpdaterPreviewType(traderItemList, preview);
            lastSelectedTraderItemList = currentSelectedTraderItemList;
        } else if(currentSelectedBuyCard != lastSelectedBuyCard) {
            DZLDisplayHelper.UpdaterPreviewType(buyCard, preview);
            lastSelectedBuyCard = currentSelectedBuyCard;
        }
    }

    private void SetCategoryItems(string categoryName) {
        traderItemList.ClearItems();

        ref array<ref DZLTraderType> items = displayCategories.Get(categoryName);

        if(items) {
            foreach(DZLTraderType type: items) {

                int sellPrice = type.CalculateDynamicSellPrice(GetCurrentStorageByName(type.type));
                sellPrice = DZLTraderHelper.GetQuantityPrice(sellPrice);
                int buyPrice = type.CalculateDynamicBuyPrice(GetCurrentStorageByName(type.type));

                string sellPriceText = "";
                if(type.sellPrice > 0) {
                    sellPriceText = sellPrice.ToString();
                }

                int index = traderItemList.AddItem(type.displayName, type, 0);
                traderItemList.SetItem(index, buyPrice.ToString(), type, 1);
                traderItemList.SetItem(index, sellPriceText, type, 2);
                traderItemList.SetItem(index, type.GetStorageString(GetCurrentStorageByName(type.type)), type, 3);
            }
        }
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        if(w == tradeButton) {
            array<string> buyItems = new array<string>;
            array<EntityAI> sellItems = new array<EntityAI>;
            int countBuyItems = buyCard.GetNumItems();
            int countSellItems = sellCard.GetNumItems();

            DZLTraderType buyItem;
            EntityAI sellItem;

            for(x = 0; x < countSellItems; x++) {
                sellItem = null;
                sellCard.GetItemData(x, 0, sellItem);
                if(sellItem) {
                    CarScript carsScript = CarScript.Cast(sellItem);
                    if(!carsScript) {
                        sellItems.Insert(sellItem);
                    } else if(!carsScript.isSold && carsScript.ownerId == player.GetPlayerId()) {
                        bool carIsEmpty = true;
                        for(int seat = 0; seat < carsScript.CrewSize(); seat++) {
                            if(carsScript.CrewMember(seat)) {
                                player.DisplayMessage("#car_is_not_empty");
                                return true;
                            }
                        }

                        sellItems.Insert(sellItem);
                        carsScript.isSold = true;
                    }
                }
            }

            bool carBuy = false;
            for(x = 0; x < countBuyItems; x++) {
                buyItem = null;
                buyCard.GetItemData(x, 0, buyItem);
                if(buyItem) {
                    if(buyItem.isCar) {
                        array<Object> excludedObjects = new array<Object>;
                        array<Object> nearbyObjects = new array<Object>;

                        if(carBuy) {
                            player.DisplayMessage("#you_can_only_buy_one_car_per_trade");
                            return true;
                        }

                        carBuy = true;
                    }

                    buyItems.Insert(buyItem.GetId());
                }
            }

            if(buyItems.Count() == 0 && sellItems.Count() == 0) {
                UpdateGUI("#you_have_to_trade_minimum_one_item");
                return true;
            }

            if(sumInt > player.GetDZLPlayer().GetMoney()) {
                UpdateGUI("#error_not_enough_money");
                return true;
            }

            g_Game.RPCSingleParam(player, DZL_RPC.TRADE_ACTION, new Param3<ref array<string>, ref array<EntityAI>, ref DZLTraderPosition>(buyItems, sellItems, position), true);
        } else if(w == itemCategory) {
            int categoryIndex = itemCategory.GetCurrentItem();
            string name = addedCats.Get(categoryIndex);

            if(name) {
                SetCategoryItems(name);
            }
        } else if(w == closeButton) {
            OnHide();
            return true;
        }

        return true;
    }

    override bool OnDoubleClick(Widget w, int x, int y, int button) {
        DZLTraderType type;
        if(w == inventory) {
            type = MoveItemFromListWidgetToListWidgetInventory(inventory, sellCard, -1);
            UpdateItemOnList(type, traderItemList, false);
            UpdateItemOnList(type, inventory, true);
        } else if(w == sellCard) {
            type = MoveItemFromListWidgetToListWidgetInventory(sellCard, inventory, 1);
            UpdateItemOnList(type, traderItemList, false);
            UpdateItemOnList(type, inventory, true);
        } else if(w == traderItemList) {
            type = MoveItemFromListWidgetToListWidgetTrader(traderItemList, buyCard, false, 1);
            UpdateItemOnList(type, traderItemList, false);
            UpdateItemOnList(type, inventory, true);
        } else if(w == buyCard) {
            type = MoveItemFromListWidgetToListWidgetTrader(buyCard, traderItemList, true, -1);
            UpdateItemOnList(type, traderItemList, false);
            UpdateItemOnList(type, inventory, true);
        }

        return true;
    }

    override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.TRADE_ACTION_RESPONSE) {
            Param1<string> paramGetResponse;
            if(ctx.Read(paramGetResponse)) {
                UpdateGUI(paramGetResponse.param1);
            }
        } else if(rpc_type == DZL_RPC.EVENT_GET_CONFIG_TRADER_STORAGE_RESPONSE) {
            Param1<ref array<ref DZLTraderTypeStorage>> traderStorageResponse;
            if(ctx.Read(traderStorageResponse)) {
                storageOfItems = traderStorageResponse.param1;

                RenderView();
            }

        }
    }

    private DZLTraderType MoveItemFromListWidgetToListWidgetInventory(TextListboxWidget sourceWidget, TextListboxWidget targetWidget, int factor) {
        int pos = sourceWidget.GetSelectedRow();
        if(pos == -1) return null;

        EntityAI item;
        sourceWidget.GetItemData(pos, 0, item);
        DZLTraderType type;
        sourceWidget.GetItemData(pos, 1, type);

        if(!item) return null;
        if(!type) return null;

        DZLTraderTypeStorage storage = GetCurrentStorageByName(type.type);
        if(-1 == factor && type.isStorageItem && storage && storage.IsStorageFull()) return null;

        string name = "";
        sourceWidget.GetItemText(pos, 0, name);
        int index;
        index = targetWidget.AddItem(name, item, 0);
        string price = "";
        sourceWidget.GetItemText(pos, 1, price);

        targetWidget.SetItem(index, price, type, 1);
        string quantity = "";
        sourceWidget.GetItemText(pos, 2, quantity);
        targetWidget.SetItem(index, quantity, item, 2);

        float itemSum = price.ToInt() * factor;
        float itemTax = itemSum / 100 * config.bankConfig.sellTradingTax;

        sumInt += Math.Round(itemSum);
        taxInt -= Math.Round(itemTax);

        UpdateSum();

        sourceWidget.RemoveRow(pos);

        if(1 == factor && storage) {
            storage.StorageDown();
        } else if(storage) {
            storage.StorageUp(DZLTraderHelper.GetQuantity(item));
        }

        if(0 == sourceWidget.GetNumItems()) {
            sourceWidget.ClearItems();
        } else {
            sourceWidget.SelectRow(0);
        }

        return type;
    }

    private DZLTraderType MoveItemFromListWidgetToListWidgetTrader(TextListboxWidget sourceWidget, TextListboxWidget targetWidget, bool removeRow, int factor) {
        int pos = sourceWidget.GetSelectedRow();
        if(pos == -1) {
            return null;
        }
        DZLTraderType itemType;
        sourceWidget.GetItemData(pos, 0, itemType);

        DZLTraderTypeStorage storage = GetCurrentStorageByName(itemType.type);
        int buyPrice = itemType.CalculateDynamicBuyPrice(storage);

        if(!itemType || itemType.isStorageItem && storage && storage.IsStorageEmpty() && !removeRow) return null;
        if(buyPrice <= 0) return null;

        sumInt = sumInt + buyPrice * factor;
        UpdateSum();

        if(removeRow) {
            sourceWidget.RemoveRow(pos);
        } else {
            string name = "";
            sourceWidget.GetItemText(pos, 0, name);

            int index;
            index = targetWidget.AddItem(name, itemType, 0);
            targetWidget.SetItem(index, buyPrice.ToString(), itemType, 1);
        }

        if(1 == factor && storage) {
            storage.StorageDown();
        } else if(storage) {
            storage.StorageUp(1.0);
        }

        return itemType;
    }

    private void UpdateSum() {
        int displaySum = sumInt * -1;
        sum.SetText(displaySum.ToString());
        tax.SetText(taxInt.ToString());

        if(displaySum >= 0) {
            sum.SetColor(ARGB(255, 0, 94, 23));
        } else {
            sum.SetColor(ARGB(255, 143, 18, 18));
        }
    }

    private void UpdateItemOnList(DZLTraderType type, TextListboxWidget widgetToChange, bool targetIsInventory) {
        if(!type) return;
        if(!type.isStorageItem) return;
        if(!targetIsInventory && type.buyPrice <= 0) return;
        if(targetIsInventory && type.sellPrice <= 0) return;

        int count = widgetToChange.GetNumItems();

        for(int x = 0; x < count; x++) {
            DZLTraderType itemType;
            widgetToChange.GetItemData(x, 1, itemType);

            if(!itemType) continue;

            if(itemType.GetId() == type.GetId()) {
                int sellPrice = 0;
                DZLTraderTypeStorage storage = GetCurrentStorageByName(type.type);
                if(!targetIsInventory) {
                    int buyPrice = itemType.CalculateDynamicBuyPrice(storage);
                    sellPrice = itemType.CalculateDynamicSellPrice(storage);
                    sellPrice = DZLTraderHelper.GetQuantityPrice(sellPrice);
                    widgetToChange.SetItem(x, buyPrice.ToString(), itemType, 1);
                    widgetToChange.SetItem(x, sellPrice.ToString(), itemType, 2);
                    widgetToChange.SetItem(x, itemType.GetStorageString(storage), itemType, 3);
                } else {
                    EntityAI item;
                    widgetToChange.GetItemData(x, 0, item);
                    sellPrice = itemType.CalculateDynamicSellPrice(storage);
                    sellPrice = DZLTraderHelper.GetQuantityPrice(sellPrice, item);

                    widgetToChange.SetItem(x, sellPrice.ToString(), itemType, 1);
                    widgetToChange.SetItem(x, itemType.GetStorageString(storage), item, 3);
                }
            }
        }
    }

    private DZLTraderTypeStorage GetCurrentStorageByName(string name) {
        if(storageOfItems) {
            foreach(DZLTraderTypeStorage storage: storageOfItems) {
                if(name == storage.GetType()) {
                    return storage;
                }
            }
        }

        return null;
    }

}
