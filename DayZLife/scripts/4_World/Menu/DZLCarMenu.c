class DZLCarMenu : DZLBaseMenu
{
	private TextListboxWidget carPanelOnlinePlayerList;
	private TextListboxWidget carPanelKeyOwnerList;
	private ButtonWidget carKeySaveButton;
	private ButtonWidget carKeySearchButton;
	private EditBoxWidget carKeySearchInput;
	private CarScript car;
	private ref array<ref DZLOnlinePlayer> keyOwner;
	private ref array<ref DZLOnlinePlayer> onlinePlayers;

	void DZLCarMenu() {
	    Construct();
	}
	void ~DZLCarMenu() {
	    Destruct();
	}

    override Widget Init() {
		layoutPath = "DayZLife/layout/CarKey/DZL_CarKey.layout";
        super.Init();

		carPanelOnlinePlayerList = creator.GetTextListboxWidget("playerList");
		carPanelKeyOwnerList = creator.GetTextListboxWidget("playerhaveKeylist");
		carKeySaveButton = creator.GetButtonWidget("safeKeylist");
		carKeySearchButton = creator.GetButtonWidget("searchButton");
		carKeySearchInput = creator.GetEditBoxWidget("search_input");

		return layoutRoot;
    }

    void SetCar(CarScript car) {
        this.car = car;
    }
	
	override void OnShow() {
		super.OnShow();
		
        GetGame().RPCSingleParam(car, DAY_Z_LIFE_GET_CAR_KEYS, null, true);
        GetGame().RPCSingleParam(null, DAY_Z_LIFE_GET_DAY_Z_LIFE_ALL_PLAYER_ONLINE_PLAYERS_FOR_ALL, null, true);
	}
	
	override bool OnDoubleClick(Widget w, int x, int y, int button) {
		if (w == carPanelOnlinePlayerList) {
		    DZLDisplayHelper.MoveDZLOnlinePlayerFromListWidgetToListWidget(carPanelOnlinePlayerList, carPanelKeyOwnerList);
		} else if (w == carPanelKeyOwnerList) {
		    DZLDisplayHelper.MoveDZLOnlinePlayerFromListWidgetToListWidget(carPanelKeyOwnerList, carPanelOnlinePlayerList);
		}
		
		return false;
	}
	
	override bool OnClick(Widget w, int x, int y, int button) {
		if (super.OnClick(w, x, y, button)) return true;

		if (w == carKeySaveButton) {
            GetGame().RPCSingleParam(player, DAY_Z_LIFE_GET_UPDATE_CAR_KEYS, new Param2<CarScript, ref array<string>>(car, DZLDisplayHelper.GetPlayerIdsFromList(carPanelKeyOwnerList)), true);
			carKeySearchInput.SetText("");
		} else if (w == carKeySearchButton) {
			DZLDisplayHelper.SearchOnlinePlayers(carKeySearchInput.GetText(), carPanelOnlinePlayerList, carPanelKeyOwnerList, onlinePlayers, player);
		}

		return false;
	}

	override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_GET_CAR_KEYS_RESPONSE) {
            autoptr Param1<ref array<ref DZLOnlinePlayer>> paramOnlinePlayers;
            if (ctx.Read(paramOnlinePlayers)){
                keyOwner = paramOnlinePlayers.param1;
                UpdateList();
            }
        } else if (rpc_type == DAY_Z_LIFE_GET_DAY_Z_LIFE_ALL_PLAYER_ONLINE_PLAYERS_FOR_ALL_RESPONSE) {
            autoptr Param1<ref array<ref DZLOnlinePlayer>> paramAllPlayers;
            if (ctx.Read(paramAllPlayers)){
                onlinePlayers = paramAllPlayers.param1;
                UpdateList();
            }
        }
	}


	private void UpdateList() {
	    if (keyOwner && onlinePlayers) {
            carPanelKeyOwnerList.ClearItems();
            carPanelOnlinePlayerList.ClearItems();

            foreach(DZLOnlinePlayer onlinePlayer: onlinePlayers) {
                if (player.GetPlayerId() == onlinePlayer.id) continue;
                bool hasKey = false;
                foreach(DZLOnlinePlayer keyPlayer: keyOwner) {
                    if (onlinePlayer.id == keyPlayer.id) {
                        hasKey = true;
                        break;
                    }
                }

                if (!hasKey) {
                    carPanelOnlinePlayerList.AddItem(onlinePlayer.name, onlinePlayer, 0);
                }
            }

            foreach(DZLOnlinePlayer _keyPlayer: keyOwner) {
                carPanelKeyOwnerList.AddItem(_keyPlayer.name, _keyPlayer, 0);
            }
	    }
	}
}
