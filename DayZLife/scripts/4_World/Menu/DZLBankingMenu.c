class DZLBankingMenu : UIScriptedMenu
{
    private ref DZLUIItemCreator creator;
	private ref DZLConfig config;

	TextListboxWidget playerListbox;

    ButtonWidget closeButton;
    ButtonWidget payInButton;
    ButtonWidget payOutButton;
    ButtonWidget cashTransferButton;
	
    TextWidget playerBankBalanceTextWidget;
    TextWidget balanceTextLabelWidget;
    TextWidget playerBalanceTextWidget;
    TextWidget bankBalanceTextWidget;
	
	EditBoxWidget inputDeposit;
	
    TextWidget errorMessageTextWidget;
	
    void DZLBankingMenu() {
        if(GetGame().IsClient()){
            GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
        }
    }

    void ~DZLBankingMenu() {
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
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_PLAYER_DEPOSIT_AT_BANK_DATA_RESPONSE || rpc_type == DAY_Z_LIFE_PLAYER_DEPOSIT_TO_PLAYER_RESPONSE) {
           autoptr Param3<ref DZLPlayer, ref DZLBank, string> paramGetResponse;
           if (ctx.Read(paramGetResponse)){
                bankBalanceTextWidget.SetText(paramGetResponse.param2.moneyAtBank.ToString());
                playerBalanceTextWidget.SetText(paramGetResponse.param1.money.ToString());
                playerBankBalanceTextWidget.SetText(paramGetResponse.param1.bank.ToString());
                errorMessageTextWidget.SetText(paramGetResponse.param3);
           }
       	} else if(rpc_type == DAY_Z_LIFE_ALL_PLAYER_IDENT_DATA_RESPONSE) {
			autoptr Param1<ref array<ref DZLPlayerBankInfo>> paramGetPlayerResponse;
           	if (ctx.Read(paramGetPlayerResponse)){
				playerListbox.ClearItems();
				array<ref DZLPlayerBankInfo> players = paramGetPlayerResponse.param1;
				
				DebugMessageDZL(players.ToString());
				
				foreach(DZLPlayerBankInfo reciver: players) {
					playerListbox.AddItem(reciver.name, reciver, 0);
				}
			
			}
		}
    }

    override Widget Init() {
        creator = new DZLUIItemCreator("DayZLife/layout/Banking/DZLBanking.layout");

        closeButton = creator.GetButtonWidget("Button_Closed");
        closeButton.Show(true);

        payOutButton = creator.GetButtonWidget("Button_Pay_out");
        payOutButton.Show(true);
		payInButton = creator.GetButtonWidget("Button_Deposit");
		payInButton.Show(true);
		cashTransferButton = creator.GetButtonWidget("Button_Cash_Transfer");
		cashTransferButton.Show(true);

        playerBankBalanceTextWidget = creator.GetTextWidget("DZLBank");
        playerBankBalanceTextWidget.Show(true);
        playerBalanceTextWidget = creator.GetTextWidget("DZLCash");
        playerBalanceTextWidget.Show(true);
        bankBalanceTextWidget = creator.GetTextWidget("DZLBank_Cash");
        balanceTextLabelWidget = creator.GetTextWidget("Cash_at_Bank");
		
		inputDeposit = creator.GetEditBoxWidget("Input_Deposit");
		errorMessageTextWidget = creator.GetTextWidget("Error_Message");
		
		playerListbox = creator.GetTextListboxWidget("Player_list");
        
        layoutRoot = creator.GetLayoutRoot();

        layoutRoot.Show(false);
		
		GetGame().RPCSingleParam(PlayerBaseHelper.GetPlayer(), DAY_Z_LIFE_ALL_PLAYER_IDENT_DATA, new Param1<string>(""), true);
		

        return layoutRoot;
    }
	
	override void OnShow() {
        if (config) {
            super.OnShow();
            errorMessageTextWidget.SetText("");
            playerBalanceTextWidget.SetText(PlayerBaseHelper.GetPlayer().dzlPlayer.money.ToString());
            playerBankBalanceTextWidget.SetText(PlayerBaseHelper.GetPlayer().dzlPlayer.bank.ToString());

			balanceTextLabelWidget.Show(config.bankConfig.showSumOfStoredCashInBank);
			bankBalanceTextWidget.Show(config.bankConfig.showSumOfStoredCashInBank);

			PlayerBase player = PlayerBaseHelper.GetPlayer();
			if (player.dzlBank) bankBalanceTextWidget.SetText(player.dzlBank.moneyAtBank.ToString());
			
			
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
            case payInButton:
                SendDeposit(-1);
				return true;
            case payOutButton:
                SendDeposit(1);
                return true;
			case cashTransferButton:
			 	SendToPlayer();
				return true;
			default:
				break;
        }
        return false;
    }
	
	private void SendToPlayer() {
		int deposit = inputDeposit.GetText().ToInt();
		
		if (deposit < 1) {
			errorMessageTextWidget.SetText("#error_deposit_must_be_positiv");
			return;
		}
		
		int selected = playerListbox.GetSelectedRow();
		
		if (-1 == selected) {
			errorMessageTextWidget.SetText("#error_no_player_was_selected");
			return;
		}
		
		DZLPlayerBankInfo player;

		playerListbox.GetItemData(selected, 0, player);
		
		if (!player) {
			errorMessageTextWidget.SetText("#error_no_player_was_selected");
			return;
		}
		
		if (player.id == PlayerBaseHelper.GetPlayer().GetIdentity().GetId()) {
			errorMessageTextWidget.SetText("#error_you_cant_send_money_to_yourself");
			return;
		}
		
		if (deposit != 0) {
            if (deposit <= PlayerBaseHelper.GetPlayer().dzlPlayer.money + PlayerBaseHelper.GetPlayer().dzlPlayer.bank) {
                GetGame().RPCSingleParam(PlayerBaseHelper.GetPlayer(), DAY_Z_LIFE_PLAYER_DEPOSIT_TO_PLAYER, new Param3<PlayerBase, DZLPlayerBankInfo, int>(PlayerBaseHelper.GetPlayer(), player, deposit), true);
                errorMessageTextWidget.SetText("");
                inputDeposit.SetText("");
            } else {
                errorMessageTextWidget.SetText("#error_not_enough_money_to_transfer");
            }
        } else {
            errorMessageTextWidget.SetText("#error_deposit_is_not_a_int");
        }
	}


    private void SendDeposit(int factor) {
        if (inputDeposit.GetText().ToInt() >= 1) {
			int deposit = factor * inputDeposit.GetText().ToInt();
            if (deposit >= PlayerBaseHelper.GetPlayer().dzlPlayer.money || deposit <= PlayerBaseHelper.GetPlayer().dzlPlayer.bank) {
                GetGame().RPCSingleParam(PlayerBaseHelper.GetPlayer(), DAY_Z_LIFE_PLAYER_DEPOSIT_AT_BANK_DATA, new Param2<PlayerBase, int>(PlayerBaseHelper.GetPlayer(), deposit), true);
                errorMessageTextWidget.SetText("");
                inputDeposit.SetText("");
            } else {
                errorMessageTextWidget.SetText("#error_not_enough_money_to_transfer");
            }
        } else if(inputDeposit.GetText().ToInt() <= 1){
			errorMessageTextWidget.SetText("#error_deposit_must_be_positiv");
		} else {
            errorMessageTextWidget.SetText("#error_deposit_is_not_a_int");
        }
	}

}