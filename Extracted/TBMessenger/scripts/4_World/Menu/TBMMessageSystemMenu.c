class TBMMessageSystemMenu : TBMBaseMenu
{
    private static int LAST_CLICK_CONTACT = 1;
    private static int LAST_CLICK_ALL_PLAYER = 2;
    private static int LAST_CLICK_MESSAGE = 3;
    private static int IN_BOX = 1;
    private static int OUT_BOX = 2;
    private int lastClick = 0;
    private int selectedBox = 1;
	private bool canSendToAll = false;

	private ButtonWidget deleteMessageButton;
	private EditBoxWidget searchContactWidget;
	private ButtonWidget searchContactButton;
	private EditBoxWidget searchOnlineWidget;
	private ButtonWidget searchOnlineButton;
	private ButtonWidget sendGlobalButton;
	private ButtonWidget sendToPlayerButton;
	private ButtonWidget outBoxButton;
	private ButtonWidget inBoxButton;
	private TextListboxWidget contactListWidget;
	private TextListboxWidget onlinePlayerListWidget;
	private TextListboxWidget messageListWidget;
	private MultilineTextWidget readWidget;
	private EditBoxWidget writeWidget;
	private Widget onlinePlayersWidget;
	private vector messagePosition;
	private Widget globalBoarder;
	private ref array<ref TBMOnlinePlayer> onlinePlayers;

	private CheckBoxWidget sendAnonymousBox;

	void TBMMessageSystemMenu() {
	    layoutPath = "TBMessenger/layout/Message/TBM_Message_Menu.layout";
        Construct();
	}

    void ~TBMMessageSystemMenu() {
        Destruct();
    }

    override Widget Init() {
        super.Init();
		deleteMessageButton = creator.GetButtonWidget("deleteButton");
		inBoxButton = creator.GetButtonWidget("inBoxButton");
		outBoxButton = creator.GetButtonWidget("outBoxButton");
		onlinePlayersWidget = creator.GetWidget("onlinePlayersWidget");
		globalBoarder = creator.GetWidget("PanelWidget13");
		searchContactWidget = creator.GetEditBoxWidget("searchKontakt");
		searchContactButton = creator.GetButtonWidget("searchKontaktButton");
		searchOnlineWidget = creator.GetEditBoxWidget("addKontakt");
		searchOnlineButton = creator.GetButtonWidget("addSearchKontaktButton");
		
		sendGlobalButton = creator.GetButtonWidget("sendGlobalButton");
		sendToPlayerButton = creator.GetButtonWidget("sendButton");
		contactListWidget = creator.GetTextListboxWidget("contactsListbox");
		onlinePlayerListWidget = creator.GetTextListboxWidget("allPlayerListbox");
		messageListWidget = creator.GetTextListboxWidget("messageListbox");
		readWidget = creator.GetMultilineTextWidget("readText");
		writeWidget = creator.GetEditBoxWidget("writeMessage");

		sendAnonymousBox = creator.GetCheckBoxWidget("checkSendAnonym");
		
		GetGame().RPCSingleParam(player, DAY_Z_LIFE_RECEIVE_ONLINE_PLAYERS, null, true);

        return layoutRoot;
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        if (super.OnClick(w, x, y, button)) return true;

        switch(w) {
            case sendToPlayerButton:
                SendMessage(TBMMessage.TYPE_PRIVATE);
                break;
            case sendGlobalButton:
                SendMessage(TBMMessage.TYPE_GLOBAL);
                break;
            case messageListWidget:
                if(selectedBox == IN_BOX) {
                    lastClick = LAST_CLICK_MESSAGE;
                    sendToPlayerButton.SetText("#replay_to_player");
                }
                sendToPlayerButton.Show(selectedBox == IN_BOX);

                DisplayMessage();
                break;
            case onlinePlayerListWidget:
                lastClick = LAST_CLICK_ALL_PLAYER;
                sendToPlayerButton.SetText("#send_to_online_player");
                sendToPlayerButton.Show(true);
                break;
            case contactListWidget:
                lastClick = LAST_CLICK_CONTACT;
                sendToPlayerButton.SetText("#send_to_contact");
                sendToPlayerButton.Show(true);
                break;
            case inBoxButton:
                selectedBox = IN_BOX;
                sendToPlayerButton.Show(true);
                RefreshMessageSystem();
                break;
            case outBoxButton:
                selectedBox = OUT_BOX;
                RefreshMessageSystem();
                break;
            case deleteMessageButton:
                DeleteMessage();
                break;
            case searchContactButton:
                TBMDisplayHelper.SearchOnlinePlayers(searchContactWidget.GetText(), contactListWidget, onlinePlayerListWidget, onlinePlayers);
                break;
            case searchOnlineButton:
                TBMDisplayHelper.SearchOnlinePlayers(searchOnlineWidget.GetText(), onlinePlayerListWidget, contactListWidget, onlinePlayers);
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
		canSendToAll = config.CanSendToAll(player.GetPlayerId());
		
        sendGlobalButton.Show(canSendToAll);
        globalBoarder.Show(canSendToAll);

        onlinePlayersWidget.Show(config.messageConfig.showOnlinePlayersInMessageMenu);

        RefreshMessageSystem();
    }

	override void HandleEventsTBM(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_RECEIVE_ONLINE_PLAYERS_RESPONSE) {
           autoptr Param1<ref array<ref TBMOnlinePlayer>> onlinePlayersParam;
           if (ctx.Read(onlinePlayersParam)){
                onlinePlayers = onlinePlayersParam.param1;
                onlinePlayerListWidget.ClearItems();
                contactListWidget.ClearItems();
                foreach(TBMOnlinePlayer onlinePlayer: onlinePlayers) {
                    if (TBMMessageDB.Get().HasContact(onlinePlayer)) {
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

	    array<ref TBMMessage>messages;
	    if(selectedBox == IN_BOX) {
	        messages = TBMMessageDB.Get().GetMessages();
	    } else {
	        messages = TBMMessageDB.Get().GetAnswers();
	    }

	    for(int x = messages.Count(); 0 < x; x--) {
	        TBMMessage message = messages.Get(x - 1);
	        
			if (message) {
				int index = messageListWidget.AddItem(message.GetSender(), message, 0);
				
				if (message.GetDate()) {
					messageListWidget.SetItem(index, message.GetDate().ToDateString(), message, 1);
				}
	            
	            messageListWidget.SetItem(index, message.GetShortText(), message, 2);
				
				if (!message.IsRead()) {
				    messageListWidget.SetItemColor(index, 0, ARGB(255,0,255,0));
				    messageListWidget.SetItemColor(index, 1, ARGB(255,0,255,0));
				    messageListWidget.SetItemColor(index, 2, ARGB(255,0,255,0));
				}
			}
	    }
	}



	private void DisplayMessage() {
	    int pos = messageListWidget.GetSelectedRow();
        if (pos == -1) {
            return;
        }
        TBMMessage message;
        messageListWidget.GetItemData(pos, 0, message);
        if (message) {
            string text = message.GetText();
            text = text + "\n-------------------------------------------------------------------\n";
            text = text + message.GetReplay();

            readWidget.SetText(text);
            if (!message.IsRead()) {
                message.Read();
                messageListWidget.SetItemColor(pos, 0, ARGB(255,255,255,255));
                messageListWidget.SetItemColor(pos, 1, ARGB(255,255,255,255));
                messageListWidget.SetItemColor(pos, 2, ARGB(255,255,255,255));
            }
        }
	}

	private void DeleteMessage() {
	    int pos = messageListWidget.GetSelectedRow();
        if (pos == -1) {
            return;
        }
        TBMMessage message;
        messageListWidget.GetItemData(pos, 0, message);
        if (message) {
			if(selectedBox == IN_BOX) {
            	TBMMessageDB.Get().RemoveMessage(message);
			} else {
				TBMMessageDB.Get().RemoveAnswer(message);
			}
            
			readWidget.SetText("");
			RefreshMessageSystem();
        }
	}

	private void AddToContact() {
	    int pos = onlinePlayerListWidget.GetSelectedRow();
        if (pos == -1) {
            return;
        }
        TBMOnlinePlayer onlinePlayer;
        onlinePlayerListWidget.GetItemData(pos, 0, onlinePlayer);

        if (onlinePlayer) {
			TBMMessageDB.Get().AddContact(onlinePlayer);
            contactListWidget.AddItem(onlinePlayer.name, onlinePlayer, 0);
            onlinePlayerListWidget.RemoveRow(pos);
        }
	}
	private void RemoveFromContact() {
	    int pos = contactListWidget.GetSelectedRow();
        if (pos == -1) {
            return;
        }
        TBMOnlinePlayer onlinePlayer;
        contactListWidget.GetItemData(pos, 0, onlinePlayer);

        if (onlinePlayer) {
            TBMMessageDB.Get().RemoveContact(onlinePlayer);
            onlinePlayerListWidget.AddItem(onlinePlayer.name, onlinePlayer, 0);
            contactListWidget.RemoveRow(pos);
        }
	}

	private void SendMessage(string type) {
	    string id = "";
	    TBMMessage message;
        if (TBMMessage.TYPE_PRIVATE == type) {
            int pos = -1;

            if (lastClick == LAST_CLICK_CONTACT) {
			    pos = contactListWidget.GetSelectedRow();
				if (pos + 1 > contactListWidget.GetNumItems()) {
					return;
				}
            } else if (lastClick == LAST_CLICK_ALL_PLAYER) {
			    pos = onlinePlayerListWidget.GetSelectedRow();
				if (pos + 1 > onlinePlayerListWidget.GetNumItems()) {
					return;
				}
            } else if (lastClick == LAST_CLICK_MESSAGE) {
			    pos = messageListWidget.GetSelectedRow();
				if (pos + 1 > messageListWidget.GetNumItems()) {
					return;
				}
            }

	        if (pos == -1) {
	            return;
	        }

            TBMOnlinePlayer onlinePlayer;

            if (lastClick == LAST_CLICK_CONTACT) {
                contactListWidget.GetItemData(pos, 0, onlinePlayer);
            } else if (lastClick == LAST_CLICK_ALL_PLAYER) {
                onlinePlayerListWidget.GetItemData(pos, 0, onlinePlayer);
            } else if (lastClick == LAST_CLICK_MESSAGE) {
                messageListWidget.GetItemData(pos, 0, message);
            }

            if (!onlinePlayer && !message) {
                player.DisplayMessage("#nothing_is_selected");
                return;
            } else if (onlinePlayer) {
                id = onlinePlayer.id;
            } else if (message) {
                id = message.GetSenderId();
                if (!id) {
                    player.DisplayMessage("#you_can_not_answer_this_message_missing_sender_id");
                    return;
                }
                bool playerIsOnline = false;
                foreach(TBMOnlinePlayer _onlinePlayer: onlinePlayers) {
                    if (_onlinePlayer.id == id) {
                        playerIsOnline = true;
                        break;
                    }
                }

                if (!playerIsOnline) {
                    player.DisplayMessage("#recipient_is_not_online_you_can_not_answer");
                    return;
                }
            }
        } else {
			if(!config.CanSendToAll(player.GetPlayerId())) return;
		}

        string text = writeWidget.GetText();
        if (text == "") {
            player.DisplayMessage("#message_is_empty");
            return;
        }
		
		bool anonym = sendAnonymousBox.IsChecked();

        GetGame().RPCSingleParam(player, DAY_Z_LIFE_SEND_MESSAGE, new Param4<string, string, string, bool>(id, text, type, !anonym), true, player.GetIdentity());
        player.DisplayMessage("#message_was_send");
		writeWidget.SetText("");

		if (message) {
            TBMMessageDB.Get().AddAnswer(player, id, text, message);
            message.Answer();
		}
	}
}
