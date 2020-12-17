class DZLDisplayHelper
{
    static string GetItemDisplayName(string itemClassname){
        string displayName;
        string cfg = CFG_VEHICLESPATH + " " + itemClassname + " displayName";
        GetGame().ConfigGetText(cfg, displayName);

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
	
	

}
