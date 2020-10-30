class DZLLicenceMenu : UIScriptedMenu
{
    private ref DZLUIItemCreator creator;
	private ref DZLConfig config;

	PlayerBase player;
    DZLPlayer dzlPlayer;

	TextListboxWidget playerListbox;

    ButtonWidget closeButton;
    ButtonWidget buyButton;
	
	TextListboxWidget licenceListBox;
	
	EditBoxWidget inputDeposit;
	
    TextWidget errorMessageTextWidget;
	
    void DZLLicenceMenu() {
        if(GetGame().IsClient()){
            GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
        }
    }

    void ~DZLLicenceMenu() {
        OnHide();
        if(GetGame().IsClient()){
            GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
        }
    }

    void SetConfig(ref DZLConfig config) {
        this.config = config;
    }

    void UpdateGUI(string message = "") {
        if(message) errorMessageTextWidget.SetText(message);
		
		array<ref DZLLicence> licences = config.licenceConfig.licences;
		licenceListBox.ClearItems();
		foreach(DZLLicence licence: licences){
			string hasLicenseText = "x";
			if (!dzlPlayer.HasLicense(licence)) {
				hasLicenseText = "";
			}
			
			int pos = licenceListBox.AddItem(licence.name, licence, 0);
			licenceListBox.SetItem(pos, licence.price.ToString(), licence, 1);
			licenceListBox.SetItem(pos, licence.dependencyLicence, licence, 2);
			licenceListBox.SetItem(pos, hasLicenseText, licence, 3);
		}
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_BUY_LICENCE_RESPONSE) {
           autoptr Param2<ref DZLPlayer, string> paramGetResponse;
           if (ctx.Read(paramGetResponse)){
				dzlPlayer = paramGetResponse.param1;
				UpdateGUI(paramGetResponse.param2);
           }
		}
    }

    override Widget Init() {
        creator = new DZLUIItemCreator("DayZLife/layout/Licence/Licence_Menu.layout");

        closeButton = creator.GetButtonWidget("Button_Closed");
        closeButton.Show(true);

        buyButton = creator.GetButtonWidget("Button_Buy");
        buyButton.Show(false);
		
		errorMessageTextWidget = creator.GetTextWidget("Error_Message");
		licenceListBox = creator.GetTextListboxWidget("Licence_ListBox");
        
        layoutRoot = creator.GetLayoutRoot();

        layoutRoot.Show(false);
		
		player = PlayerBaseHelper.GetPlayer();
		dzlPlayer = player.dzlPlayer;

        return layoutRoot;
    }
	
	override void OnShow() {
        if (config) {
            super.OnShow();
			buyButton.Show(false);
            errorMessageTextWidget.SetText("");
			UpdateGUI();
			
			GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_INVENTORY);
            GetGame().GetUIManager().ShowCursor(true);
            GetGame().GetInput().ChangeGameFocus(1);
        } else {
            OnHide();
        }
    }

    override void OnHide() {
        super.OnHide();

        GetGame().GetUIManager().ShowCursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(true);
        Close();
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        super.OnClick(w, x, y, button);
        switch(w){
            case closeButton:
                OnHide();
                return true;
            case buyButton:
				int position = licenceListBox.GetSelectedRow();
				
				if(-1 == position) return true;
				DZLLicence licence;
				licenceListBox.GetItemData(position, 0, licence);
				
				if(!licence) return true;
			
				string messege = dzlPlayer.CanBuyLicence(licence);
			
				if("" == messege){
					GetGame().RPCSingleParam(player, DAY_Z_LIFE_BUY_LICENCE, new Param2<PlayerBase, ref DZLLicence>(player, licence), true);
				} else {
					UpdateGUI(messege);
				}
				
				return true;
			case licenceListBox:
				buyButton.Show(true);
				return true;
			default:
				break;
        }
        return false;
    }	
}