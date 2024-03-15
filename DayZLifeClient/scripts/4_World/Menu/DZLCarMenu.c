class DZLCarMenu : DZLBaseMenu {
    private TextListboxWidget carPanelOnlinePlayerList;
    private TextListboxWidget carPanelKeyOwnerList;
    private TextWidget newOwnerDisplay;
    private ButtonWidget changOwnerButton;
    private ButtonWidget carKeySaveButton;
    private ButtonWidget carKeySearchButton;
    private EditBoxWidget carKeySearchInput;
    private CarScript car;
    private ref array<ref DZLOnlinePlayer> keyOwner;
    private ref array<ref DZLOnlinePlayer> onlinePlayers;
    private DZLOnlinePlayer selectedPlayer;
    private int lastSelectedPlayerRow = -1;
    private int lastSelectedKeyRow = -1;

    void DZLCarMenu() {
        Construct();
    }
    void ~DZLCarMenu() {
        Destruct();
    }

    override Widget Init() {
        layoutPath = "DayZLifeClient/layout/CarKey/DZL_CarKey.layout";
        super.Init();

        carPanelOnlinePlayerList = creator.GetTextListboxWidget("playerList");
        carPanelKeyOwnerList = creator.GetTextListboxWidget("playerhaveKeylist");
        carKeySaveButton = creator.GetButtonWidget("safeKeylist");
        carKeySearchButton = creator.GetButtonWidget("searchButton");
        carKeySearchInput = creator.GetEditBoxWidget("search_input");

        newOwnerDisplay = creator.GetTextWidget("newOwnerDisplay");
        changOwnerButton = creator.GetButtonWidget("changOwnerButton");

        return layoutRoot;
    }

    void SetCar(CarScript _car) {
        this.car = _car;
    }

    override void OnShow() {
        super.OnShow();

        GetGame().RPCSingleParam(car, DZL_RPC.GET_CAR_KEYS, null, true);
        GetGame().RPCSingleParam(null, DZL_RPC.GET_DAY_Z_LIFE_ALL_PLAYER_ONLINE_PLAYERS_FOR_ALL, null, true);
    }

    override bool OnDoubleClick(Widget w, int x, int y, int button) {
        if(w == carPanelOnlinePlayerList) {
            DZLDisplayHelper.MoveDZLOnlinePlayerFromListWidgetToListWidget(carPanelOnlinePlayerList, carPanelKeyOwnerList, DAY_Z_LIFE_JOB_CIVIL);
        } else if(w == carPanelKeyOwnerList) {
            DZLDisplayHelper.MoveDZLOnlinePlayerFromListWidgetToListWidget(carPanelKeyOwnerList, carPanelOnlinePlayerList, DAY_Z_LIFE_JOB_CIVIL);
        }

        return false;
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        if(super.OnClick(w, x, y, button)) return true;

        if(w == carKeySaveButton) {
            GetGame().RPCSingleParam(player, DZL_RPC.GET_UPDATE_CAR_KEYS, new Param2<CarScript, ref array<DZLOnlinePlayer>>(car, DZLDisplayHelper.GetPlayerIdsAndRanksFromList(carPanelKeyOwnerList)), true);
            carKeySearchInput.SetText("");
        } else if(w == carKeySearchButton) {
            DZLDisplayHelper.SearchOnlinePlayersWithKey(carKeySearchInput.GetText(), carPanelOnlinePlayerList, carPanelKeyOwnerList, onlinePlayers, player);
        } else if(w == changOwnerButton && selectedPlayer) {
            GetGame().RPCSingleParam(player, DZL_RPC.CHANGE_CAR_OWNER, new Param2<string, CarScript>(selectedPlayer.id, car), true);
            OnHide();
        }

        return false;
    }

    override void Update(float timeslice) {
        super.Update(timeslice);
        int currentRowKey = carPanelKeyOwnerList.GetSelectedRow();
        int currentRowPlayer = carPanelOnlinePlayerList.GetSelectedRow();

        if(currentRowKey != -1 && currentRowKey != lastSelectedKeyRow) {
            carPanelKeyOwnerList.GetItemData(currentRowKey, 0, selectedPlayer);
            lastSelectedKeyRow = currentRowKey;
            newOwnerDisplay.SetText("");
            if(selectedPlayer) {
                newOwnerDisplay.SetText(selectedPlayer.name);
            }
        } else if(currentRowPlayer != -1 && currentRowPlayer != lastSelectedPlayerRow) {
            carPanelOnlinePlayerList.GetItemData(currentRowPlayer, 0, selectedPlayer);
            lastSelectedPlayerRow = currentRowPlayer;
            newOwnerDisplay.SetText("");
            if(selectedPlayer) {
                newOwnerDisplay.SetText(selectedPlayer.name);
            }
        }
    }

    override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.GET_CAR_KEYS_RESPONSE) {
            autoptr Param1<ref array<ref DZLOnlinePlayer>> paramOnlinePlayers;
            if(ctx.Read(paramOnlinePlayers)) {
                keyOwner = paramOnlinePlayers.param1;
                UpdateList();
            }
        } else if(rpc_type == DZL_RPC.GET_DAY_Z_LIFE_ALL_PLAYER_ONLINE_PLAYERS_FOR_ALL_RESPONSE) {
            autoptr Param1<ref array<ref DZLOnlinePlayer>> paramAllPlayers;
            if(ctx.Read(paramAllPlayers)) {
                onlinePlayers = paramAllPlayers.param1;
                UpdateList();
            }
        }
    }


    private void UpdateList() {
        if(keyOwner && onlinePlayers) {
            carPanelKeyOwnerList.ClearItems();
            carPanelOnlinePlayerList.ClearItems();

            foreach(DZLOnlinePlayer onlinePlayer: onlinePlayers) {
                bool hasKey = false;
                foreach(DZLOnlinePlayer keyPlayer: keyOwner) {
                    if(onlinePlayer.id == keyPlayer.id) {
                        hasKey = true;
                        break;
                    }
                }

                if(!hasKey) {
                    carPanelOnlinePlayerList.AddItem(onlinePlayer.name, onlinePlayer, 0);
                }
            }

            foreach(DZLOnlinePlayer _keyPlayer: keyOwner) {
                carPanelKeyOwnerList.AddItem(_keyPlayer.name, _keyPlayer, 0);
            }
        }
    }
}
