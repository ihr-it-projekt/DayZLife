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
	private ButtonWidget addContactButton;
	private ButtonWidget deleteContactButton;
	private ButtonWidget sendGlobalButton;
	private ButtonWidget sosCopButton;
	private ButtonWidget sendMedicButton;
	private ButtonWidget sendToPlayerButton;
	private TextListboxWidget contactListWidget;
	private TextListboxWidget onlinePlayerListWidget;
	private TextListboxWidget messageListWidget;
	private MultilineTextWidget readWidget;
	private MultilineEditBoxWidget writeWidget;
	
	void DZLMessageSystemMenu() {
	    layoutPath = "DayZLife/layout/Message/DZL_Message_Menu.layout";
        Construct();
	}

    void ~DZLMessageSystemMenu() {
        Destruct();
    }

    override Widget Init() {
        super.Init();
		deleteMessageButton = creator.GetButtonWidget("deleteMessage");
		showMapButton = creator.GetButtonWidget("showMapButton");
		mapClose = creator.GetButtonWidget("mapCloseButton");
		mapWidget = creator.GetMapWidget("sosMap");
		searchContactWidget = creator.GetEditBoxWidget("searchKontakt");
		searchContactButton = creator.GetButtonWidget("searchKontaktButton");
		searchOnlineWidget = creator.GetEditBoxWidget("addKontakt");
		searchOnlineButton = creator.GetButtonWidget("addSearchKontaktButton");
		
		addContactButton = creator.GetButtonWidget("addContactsButton");
		deleteContactButton = creator.GetButtonWidget("deleteContactsButton");
		sendGlobalButton = creator.GetButtonWidget("sendGlobalButton");
		sosCopButton = creator.GetButtonWidget("sendSOSButton");
		sendMedicButton = creator.GetButtonWidget("sendMedicButton");
		sendToPlayerButton = creator.GetButtonWidget("sendButton");
		contactListWidget = creator.GetTextListboxWidget("contactsListbox");
		onlinePlayerListWidget = creator.GetTextListboxWidget("allPlayerListbox");
		messageListWidget = creator.GetTextListboxWidget("messageListbox");
		readWidget = creator.GetMultilineTextWidget("readMessage");
		writeWidget = creator.GetMultilineEditBoxWidget("writeMessage");
		

        return layoutRoot;
    }

	override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {

	}
}
