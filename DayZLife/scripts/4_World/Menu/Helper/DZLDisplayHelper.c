class DZLDisplayHelper
{
    static EntityAI previewItem;

    static string GetItemDisplayName(string itemClassname){
        TStringArray configs = new TStringArray;
        configs.Insert( CFG_VEHICLESPATH );
        configs.Insert( CFG_WEAPONSPATH );
        configs.Insert( CFG_MAGAZINESPATH );
        configs.Insert( "CfgNonAIVehicles" );
        configs.Insert( "CfgAmmo" );

        string displayName;
        foreach (string itemName: configs){
            string cfg = itemName + " " + itemClassname + " displayName";
            GetGame().ConfigGetText(cfg, displayName);

            if (displayName != ""){
                displayName.Replace("$UNT$", "");

                break;
            }
        }

        if (displayName == "") {
            displayName = itemClassname;
        }

        return displayName;
    }

    static void UpdateMap(MapWidget mapWidget, vector pos) {
        mapWidget.ClearUserMarks();
        mapWidget.SetScale(0.1);
        mapWidget.SetMapPos(pos);
        mapWidget.AddUserMark(pos, "", ARGB(255,0,255,0), "set:dayz_gui image:cartridge_pistol");
    }

    static void MoveDZLOnlinePlayerFromListWidgetToListWidget(TextListboxWidget sourceWidget, TextListboxWidget targetWidget) {
        int pos = sourceWidget.GetSelectedRow();
        if (pos == -1) {
            return;
        }
        DZLOnlinePlayer itemType;
        sourceWidget.GetItemData(pos, 0, itemType);

        if (itemType) {
            sourceWidget.RemoveRow(pos);

            targetWidget.AddItem(itemType.name, itemType, 0);

        }
    }

    static array<string> GetPlayerIdsFromList(TextListboxWidget listWidget) {
        int count = listWidget.GetNumItems();

        array<string> list = new array<string>;

        if (count > 0) {
            for (int i = 0; i < count; ++i) {
                DZLOnlinePlayer _player;
                listWidget.GetItemData(i, 0, _player);

                if (_player) {
                    list.Insert(_player.id);
                }
            }
        }

        return list;
    }

    static DZLPlayer GetDZLPlayerFromList(TextListboxWidget sourceWidget) {
        int pos = sourceWidget.GetSelectedRow();
        if (pos == -1) {
            return null;
        }
        DZLPlayer itemType;
        sourceWidget.GetItemData(pos, 0, itemType);
        return itemType;
    }


	static void SearchOnlinePlayers(string search, TextListboxWidget target, TextListboxWidget exclude, array<ref DZLOnlinePlayer> onlinePlayers, PlayerBase player) {
	    if (!onlinePlayers || onlinePlayers.Count() == 0) return;
        target.ClearItems();
        search.ToLower();
        int countPlayers = exclude.GetNumItems();

        foreach(DZLOnlinePlayer onlinePlayer: onlinePlayers) {
            if (player.GetIdentity().GetId() == onlinePlayer.id) continue;
            bool hasKey = false;

            for(int i = 0; i < countPlayers; i ++) {
                DZLOnlinePlayer keyPlayer;
                exclude.GetItemData(i, 0, keyPlayer);
                if (!keyPlayer) continue;

                if (onlinePlayer.id == keyPlayer.id) {
                    hasKey = true;
                    break;
                }
            }
            if (hasKey) continue;

            string playerNameLow = onlinePlayer.name;
            playerNameLow.ToLower();
            if (search == "" || playerNameLow.Contains(search)) {
                target.AddItem(onlinePlayer.name, onlinePlayer, 0);
            }
        }
    }
	static void SearchOnlinePlayersSingleWiget(string search, TextListboxWidget target, array<ref DZLPlayer> onlinePlayers) {
	    if (!onlinePlayers || onlinePlayers.Count() == 0) return;
        target.ClearItems();
        search.ToLower();

        foreach(DZLPlayer onlinePlayer: onlinePlayers) {
            string playerNameLow = onlinePlayer.playerName;
            playerNameLow.ToLower();
            if (search == "" || playerNameLow.Contains(search)) {
                target.AddItem(onlinePlayer.playerName, onlinePlayer, 0);
            }
        }
    }

	static void MoveItemFromListWidgetToListWidget(TextListboxWidget sourceWidget, TextListboxWidget targetWidget) {
        int pos = sourceWidget.GetSelectedRow();
        if (pos == -1) {
            return;
        }
        EntityAI item;
        sourceWidget.GetItemData(pos, 0, item);

        if (item) {
            string name = "";
            sourceWidget.GetItemText(pos, 0, name);
            int index;
            index = targetWidget.AddItem(name, item, 0);
            sourceWidget.RemoveRow(pos);
        }
    }

	static void MoveStoreItemFromListWidgetToListWidget(TextListboxWidget sourceWidget, TextListboxWidget targetWidget) {
        int pos = sourceWidget.GetSelectedRow();
        if (pos == -1) {
            return;
        }
        DZLStoreItem item;
        sourceWidget.GetItemData(pos, 0, item);
        if (item) {
            string name = "";
            sourceWidget.GetItemText(pos, 0, name);
            int index;
            index = targetWidget.AddItem(name, item, 0);
            sourceWidget.RemoveRow(pos);
        }
    }

    static void UpdaterPreviewByEntityAI(TextListboxWidget widget, ItemPreviewWidget preview) {
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
    static void UpdaterPreviewByStoreItem(TextListboxWidget widget, ItemPreviewWidget preview) {
        int pos = widget.GetSelectedRow();
        if (pos == -1) {
            return;
        }
        DZLStoreItem itemType;
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

    static void UpdaterPreviewType(TextListboxWidget widget, ItemPreviewWidget preview) {
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

    static void DeletePreviewItem() {
        if(previewItem) {
            GetGame().ObjectDelete(previewItem);
        }
    }

}
