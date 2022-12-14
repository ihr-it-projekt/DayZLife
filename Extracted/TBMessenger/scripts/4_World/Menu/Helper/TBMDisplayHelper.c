class TBMDisplayHelper
{
    static EntityAI previewItem;


	static void SearchOnlinePlayers(string search, TextListboxWidget target, TextListboxWidget exclude, array<ref TBMOnlinePlayer> onlinePlayers) {
	    if (!onlinePlayers || onlinePlayers.Count() == 0) return;
        target.ClearItems();
        search.ToLower();
        int countPlayers = exclude.GetNumItems();

        foreach(TBMOnlinePlayer onlinePlayer: onlinePlayers) {
            bool mustExclude = false;
            for(int i = 0; i < countPlayers; i ++) {
                TBMOnlinePlayer keyPlayer;
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


}
