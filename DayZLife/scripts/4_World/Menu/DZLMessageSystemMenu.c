class DZLMessageSystemMenu : DZLBaseMenu
{
	private ButtonWidget showMapButton;
	private MapWidget mapWidget;
	private ButtonWidget mapClose;
	private ButtonWidget deleteMessageButton;
	private EditBoxWidget searchContactWidget;
	private ButtonWidget searchContactButton;
	private EditBoxWidget searchOnlineWidget;
	private ButtonWidget searchOnlineButton;
	private ButtonWidget sendGlobalButton;
	private ButtonWidget sosCopButton;
	private ButtonWidget sendMedicButton;
	private ButtonWidget sendToPlayerButton;
	private TextListboxWidget contactListWidget;
	private TextListboxWidget onlinePlayerListWidget;
	private TextListboxWidget messageListWidget;
	private MultilineTextWidget readWidget;
	private MultilineEditBoxWidget writeWidget;
	private vector messagePosition;
	private ref array<ref DZLOnlinePlayer> onlinePlayers;

	void DZLMessageSystemMenu() {
	    layoutPath = "DayZLife/layout/Message/DZL_Message_Menu.layout";
        Construct();
	}

    void ~DZLMessageSystemMenu() {
        Destruct();
    }

    override Widget Init() {
        super.Init();
		deleteMessageButton = creator.GetButtonWidget("deleteButton");
		showMapButton = creator.GetButtonWidget("showMapButton");
		mapClose = creator.GetButtonWidget("mapCloseButton");
		mapWidget = creator.GetMapWidget("sosMap");
		searchContactWidget = creator.GetEditBoxWidget("searchKontakt");
		searchContactButton = creator.GetButtonWidget("searchKontaktButton");
		searchOnlineWidget = creator.GetEditBoxWidget("addKontakt");
		searchOnlineButton = creator.GetButtonWidget("addSearchKontaktButton");
		
		sendGlobalButton = creator.GetButtonWidget("sendGlobalButton");
		sosCopButton = creator.GetButtonWidget("sendSOSButton");
		sendMedicButton = creator.GetButtonWidget("sendMedicButton");
		sendToPlayerButton = creator.GetButtonWidget("sendButton");
		contactListWidget = creator.GetTextListboxWidget("contactsListbox");
		onlinePlayerListWidget = creator.GetTextListboxWidget("allPlayerListbox");
		messageListWidget = creator.GetTextListboxWidget("messageListbox");
		readWidget = creator.GetMultilineTextWidget("readText");
		writeWidget = creator.GetMultilineEditBoxWidget("writeMessage");
		
		showMapButton.Show(false);
        mapWidget.Show(false);

		GetGame().RPCSingleParam(player, DAY_Z_LIFE_RECEIVE_ONLINE_PLAYERS, null, true);

        return layoutRoot;
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        if (super.OnClick(w, x, y, button)) return true;

        switch(w) {
            case sendToPlayerButton:
                SendMessage(DZLMessage.TYPE_PRIVATE);
                break;
            case sendGlobalButton:
                SendMessage(DZLMessage.TYPE_GLOBAL);
                break;
            case sendMedicButton:
                SendMessage(DZLMessage.TYPE_MEDIC);
                break;
            case sosCopButton:
                SendMessage(DZLMessage.TYPE_COP);
                break;
            case messageListWidget:
                DisplayMessage();
                break;
            case showMapButton:
                ShowMap();
                break;
            case mapClose:
                mapWidget.Show(false);
                break;
            case deleteMessageButton:
                DeleteMessage();
                break;
            case searchContactButton:
                DZLDisplayHelper.SearchOnlinePlayers(searchContactWidget.GetText(), contactListWidget, onlinePlayerListWidget, onlinePlayers);
                break;
            case searchOnlineButton:
                DZLDisplayHelper.SearchOnlinePlayers(searchOnlineWidget.GetText(), onlinePlayerListWidget, contactListWidget, onlinePlayers);
                break;
            default:
                break;
        }
		return true;
    }

    override bool OnDoubleClick(Widget w, int x, int y, int button) {
        switch(w) {
            case onlinePlayerListWidget:
                AddToContact();
                break;
            case contactListWidget:
                RemoveFromContact();
                break;
        }
        return true;
    }

    override void OnShow() {
        super.OnShow();
        RefreshMessageSystem();
    }

    override void OnHide() {
        mapWidget.Show(false);
        super.OnHide();
    }

	override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_RECEIVE_ONLINE_PLAYERS_RESPONSE) {
           autoptr Param1<ref array<ref DZLOnlinePlayer>> onlinePlayersParam;
           if (ctx.Read(onlinePlayersParam)){
                onlinePlayers = onlinePlayersParam.param1;
                onlinePlayerListWidget.ClearItems();
                contactListWidget.ClearItems();
                foreach(DZLOnlinePlayer onlinePlayer: onlinePlayers) {
                    if (DZLMessageDB.Get().HasContact(onlinePlayer)) {
                        contactListWidget.AddItem(onlinePlayer.name, onlinePlayer, 0);
                    } else {
                        onlinePlayerListWidget.AddItem(onlinePlayer.name, onlinePlayer, 0);
                    }
                }
           }
        }
	}

	void RefreshMessageSystem() {
	    messageListWidget.ClearItems();
	    map<string, ref DZLMessage>messages = DZLMessageDB.Get().GetMessages();

	    foreach(string id, DZLMessage message: messages) {
	        int index = messageListWidget.AddItem(message.GetSender(), message, 0);
            messageListWidget.SetItem(index, message.GetDate().ToDateString(), message, 1);
            messageListWidget.SetItem(index, message.GetShortText(), message, 2);
	    }
	}

	private void ShowMap() {
	    mapWidget.Show(true);
	    DZLDisplayHelper.UpdateMap(mapWidget, messagePosition);
	}

	private void DisplayMessage() {
	    int pos = messageListWidget.GetSelectedRow();
        if (pos == -1) {
            return;
        }
        DZLMessage message;
        messageListWidget.GetItemData(pos, 0, message);
        if (message) {
            readWidget.SetText(message.GetText());
            showMapButton.Show(message.GetType() == DZLMessage.TYPE_COP);
            messagePosition = message.GetPosition();
        }
	}

	private void DeleteMessage() {
	    int pos = messageListWidget.GetSelectedRow();
        if (pos == -1) {
            return;
        }
        DZLMessage message;
        messageListWidget.GetItemData(pos, 0, message);
        if (message) {
            DZLMessageDB.Get().RemoveMessage(message);
			RefreshMessageSystem();
        }
	}

	private void AddToContact() {
	    int pos = onlinePlayerListWidget.GetSelectedRow();
        if (pos == -1) {
            return;
        }
        DZLOnlinePlayer onlinePlayer;
        onlinePlayerListWidget.GetItemData(pos, 0, onlinePlayer);

        if (onlinePlayer) {
            DZLMessageDB.Get().AddContact(onlinePlayer);
            contactListWidget.AddItem(onlinePlayer.name, onlinePlayer, 0);
            onlinePlayerListWidget.RemoveRow(pos);
        }
	}
	private void RemoveFromContact() {
	    int pos = contactListWidget.GetSelectedRow();
        if (pos == -1) {
            return;
        }
        DZLOnlinePlayer onlinePlayer;
        contactListWidget.GetItemData(pos, 0, onlinePlayer);

        if (onlinePlayer) {
            DZLMessageDB.Get().RemoveContact(onlinePlayer);
            onlinePlayerListWidget.AddItem(onlinePlayer.name, onlinePlayer, 0);
            contactListWidget.RemoveRow(pos);
        }
	}

	private void SendMessage(string type) {
	    string id = "";
        if (DZLMessage.TYPE_PRIVATE == type) {
			int pos = contactListWidget.GetSelectedRow();
	        if (pos == -1) {
	            return;
	        }
            DZLOnlinePlayer onlinePlayer;
            contactListWidget.GetItemData(pos, 0, onlinePlayer);

            if (!onlinePlayer) {
                player.DisplayMessage("#no_contact_is_selected");
                return;
            }
            id = onlinePlayer.id;
        }

        string text = "";
		writeWidget.GetText(text);
        if (text == "") {
            player.DisplayMessage("#message_is_empty");
            return;
        }

        GetGame().RPCSingleParam(player, DAY_Z_LIFE_SEND_MESSAGE, new Param3<string, string, string>(id, text, type), true, player.GetIdentity());
        player.DisplayMessage("#message_was_send");
	}
}
