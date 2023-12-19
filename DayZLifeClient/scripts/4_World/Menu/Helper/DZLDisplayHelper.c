class DZLDisplayHelper {
    static EntityAI previewItem;

    static string GetItemDisplayName(string itemClassname) {
        TStringArray configs = new TStringArray;
        configs.Insert(CFG_VEHICLESPATH);
        configs.Insert(CFG_WEAPONSPATH);
        configs.Insert(CFG_MAGAZINESPATH);
        configs.Insert("CfgNonAIVehicles");
        configs.Insert("CfgAmmo");

        string displayName;
        foreach (string itemName: configs) {
            string cfg = itemName + " " + itemClassname + " displayName";
            GetGame().ConfigGetText(cfg, displayName);

            if (displayName != "") {
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

    static void MoveDZLOnlinePlayerFromListWidgetToListWidget(TextListboxWidget sourceWidget, TextListboxWidget targetWidget, string job) {
        int pos = sourceWidget.GetSelectedRow();
        if (pos == -1) {
            return;
        }
        DZLOnlinePlayer itemType;
        sourceWidget.GetItemData(pos, 0, itemType);

        if (itemType) {
            sourceWidget.RemoveRow(pos);

            int posInsert = targetWidget.AddItem(itemType.name, itemType, 0);

            DZLPaycheck paycheck = DZLConfig.Get().jobConfig.paycheck.GetFallbackPaycheckByJob(job);
            itemType.rank = paycheck.rank;

            if (DAY_Z_LIFE_JOB_CIVIL != job) {
                targetWidget.SetItem(posInsert, itemType.rank, itemType, 1);
            }
        }
    }

    static array<ref DZLFractionMember> GetDZLFractionMemberFromList(TextListboxWidget listWidget) {
        int count = listWidget.GetNumItems();

        array<ref DZLFractionMember> list = new array<ref DZLFractionMember>;

        if (count > 0) {
            for (int i = 0; i < count; ++i) {
                DZLFractionMember _player;
                listWidget.GetItemData(i, 0, _player);

                if (_player) {
                    list.Insert(_player);
                }
            }
        }

        return list;
    }

    static void LoadDZLOnlinePlayerAndFillRankListWidget(TextListboxWidget sourceWidget, TextListboxWidget jobRankList, string job) {
        int pos = sourceWidget.GetSelectedRow();
        if (pos == -1) {
            return;
        }
        DZLOnlinePlayer itemType;
        sourceWidget.GetItemData(pos, 0, itemType);

        if (itemType) {
            array<ref DZLPaycheck> paychecks = DZLConfig.Get().jobConfig.paycheck.GetPaycheckByJob(job);


            int count = 0;
            jobRankList.ClearItems();
            foreach(DZLPaycheck paycheck: paychecks) {
                jobRankList.AddItem(paycheck.rank, paycheck, 0);

                if (paycheck.rank == itemType.rank) {
                    jobRankList.SelectRow(count);
                }

                count++;
            }
        }
    }

    static void ChangeRankFromPlayer(TextListboxWidget rankWidget, TextListboxWidget playerWidget) {
        int posPlayer = playerWidget.GetSelectedRow();
        if (posPlayer == -1) {
            return;
        }

        DZLOnlinePlayer player;
        playerWidget.GetItemData(posPlayer, 0, player);

        int posRank = rankWidget.GetSelectedRow();
        if (posRank == -1) {
            return;
        }
        DZLPaycheck paycheck;
        rankWidget.GetItemData(posRank, 0, paycheck);

        if (paycheck && player) {
            player.rank = paycheck.rank;

            playerWidget.SetItem(posPlayer, player.name, player, 0);
            playerWidget.SetItem(posPlayer, player.rank, player, 1);
        }
    }

    static array<DZLOnlinePlayer> GetPlayerIdsAndRanksFromList(TextListboxWidget listWidget) {
        int count = listWidget.GetNumItems();

        array<DZLOnlinePlayer> list = new array<DZLOnlinePlayer>;


        if (count > 0) {
            for (int i = 0; i < count; ++i) {
                DZLOnlinePlayer _player;
                listWidget.GetItemData(i, 0, _player);

                if (_player) {
                    list.Insert(_player);
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


    static void SearchOnlinePlayersWithKey(string search, TextListboxWidget target, TextListboxWidget exclude, array<ref DZLOnlinePlayer> onlinePlayers, PlayerBase player) {
        if (!onlinePlayers || onlinePlayers.Count() == 0) return;
        target.ClearItems();
        search.ToLower();
        int countPlayers = exclude.GetNumItems();

        foreach(DZLOnlinePlayer onlinePlayer: onlinePlayers) {
            if (player.GetPlayerId() == onlinePlayer.id) continue;
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

    static void SearchOnlinePlayers(string search, TextListboxWidget target, TextListboxWidget exclude, array<ref DZLOnlinePlayer> onlinePlayers) {
        if (!onlinePlayers || onlinePlayers.Count() == 0) return;
        target.ClearItems();
        search.ToLower();
        int countPlayers = exclude.GetNumItems();

        foreach(DZLOnlinePlayer onlinePlayer: onlinePlayers) {
            bool mustExclude = false;
            for(int i = 0; i < countPlayers; i ++) {
                DZLOnlinePlayer keyPlayer;
                exclude.GetItemData(i, 0, keyPlayer);
                if (!keyPlayer) continue;

                if (keyPlayer.id == onlinePlayer.id) {
                    mustExclude = true;
                    break;
                }
            }

            if (mustExclude) continue;

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

    static void SearchFractionMembersSingleWiget(string search, TextListboxWidget target, array<ref DZLFractionMember> onlinePlayers) {
        if (!onlinePlayers || onlinePlayers.Count() == 0) return;
        target.ClearItems();
        search.ToLower();

        foreach(DZLFractionMember onlinePlayer: onlinePlayers) {
            string playerNameLow = onlinePlayer.name;
            playerNameLow.ToLower();
            if (search == "" || playerNameLow.Contains(search)) {
                target.AddItem(onlinePlayer.name, onlinePlayer, 0);
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
