class DZLCarMenu : DZLBaseMenu
{
	private TextListboxWidget carPanelOnlinePlayerList;
	private TextListboxWidget carPanelKeyOwnerList;
	private ButtonWidget carKeySaveButton;
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

		return layoutRoot;
    }

    void SetCar(CarScript car) {
        this.car = car;
    }
	
	override void OnShow() {
		super.OnShow();
		
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_GET_CAR_KEYS, new Param1<CarScript>(car), true);
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_GET_ALL_PLAYERS, new Param1<PlayerBase>(player), true);
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
		}

		return false;
	}

	override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_GET_ALL_PLAYERS_RESPONSE) {
            DebugMessageDZL("DAY_Z_LIFE_GET_ALL_PLAYERS_RESPONSE");
            autoptr Param1<ref array<ref DZLOnlinePlayer>> paramOnlinePlayers;
            if (ctx.Read(paramOnlinePlayers)){
                onlinePlayers = paramOnlinePlayers.param1;
                UpdateList();
            }
        } else if (rpc_type == DAY_Z_LIFE_GET_CAR_KEYS_RESPONSE) {
            DebugMessageDZL("DAY_Z_LIFE_GET_CAR_KEYS_RESPONSE");
            autoptr Param1<ref array<ref DZLOnlinePlayer>> paramAllPlayers;
            if (ctx.Read(paramAllPlayers)){
                keyOwner = paramAllPlayers.param1;
                UpdateList();
            }
        }
	}

	private void UpdateList() {
	    DebugMessageDZL("1");
	    if (keyOwner && onlinePlayers) {
	        DebugMessageDZL("2");
            carPanelKeyOwnerList.ClearItems();
            carPanelOnlinePlayerList.ClearItems();

            foreach(DZLOnlinePlayer onlinePlayer: onlinePlayers) {
                DebugMessageDZL("3");
                if (player.GetIdentity().GetId() == onlinePlayer.id) continue;
                DebugMessageDZL("4");
                bool hasKey = false;
                foreach(DZLOnlinePlayer keyPlayer: keyOwner) {
                    if (onlinePlayer.id == keyPlayer.id) {
                        hasKey = true;
                        DebugMessageDZL("5");
                        break;
                    }
                }

                if (!hasKey) {
                    DebugMessageDZL("6");
                    carPanelOnlinePlayerList.AddItem(onlinePlayer.name, onlinePlayer, 0);
                }
            }

            foreach(DZLOnlinePlayer _keyPlayer: keyOwner) {
                DebugMessageDZL("7");
                carPanelKeyOwnerList.AddItem(_keyPlayer.name, _keyPlayer, 0);
            }
	    }
	}
}
