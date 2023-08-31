class DZLBankingMenu : DZLBaseMenu
{
	private TextListboxWidget playerListbox;
	
	private Widget wrapperFractionButtonCashToPlayer;
	private Widget wrapperFractionButtonPayout;
	private Widget wrapperFractionButtonDeposit;
	private Widget wrapperFractionCash;

    private ButtonWidget payInButton;
    private ButtonWidget payOutButton;
    private ButtonWidget cashTransferButton;
    private ButtonWidget fractionPayInButton;
    private ButtonWidget fractionPayOutButton;
    private ButtonWidget fractionCashTransferButton;

    private TextWidget playerBankBalanceTextWidget;
    private TextWidget balanceTextLabelWidget;
    private TextWidget playerBalanceTextWidget;
    private TextWidget bankBalanceTextWidget;
    private TextWidget fractionBalanceTextWidget;
    private TextWidget bankTaxTextWidget;

	private EditBoxWidget inputDeposit;
	
    void DZLBankingMenu() {
        layoutPath = "DayZLifeClient/layout/Banking/DZLBanking.layout";
        Construct();
    }

    void ~DZLBankingMenu() {
        Destruct();
    }

    override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_PLAYER_DEPOSIT_TO_PLAYER_RESPONSE) {
           autoptr Param3<ref DZLPlayer, ref DZLBank, string> paramGetResponse;
           if (ctx.Read(paramGetResponse)){
                bankBalanceTextWidget.SetText(paramGetResponse.param2.moneyAtBank.ToString());
                playerBalanceTextWidget.SetText(paramGetResponse.param1.GetMoney().ToString());
                playerBankBalanceTextWidget.SetText(paramGetResponse.param1.GetBankMoney().ToString());
                player.DisplayMessage(paramGetResponse.param3);
           }
       	} else if(rpc_type == DAY_Z_LIFE_ALL_PLAYER_IDENT_DATA_RESPONSE) {
			autoptr Param1<ref array<ref DZLPlayerBankInfo>> paramGetPlayerResponse;
           	if (ctx.Read(paramGetPlayerResponse)){
				playerListbox.ClearItems();
				array<ref DZLPlayerBankInfo> players = paramGetPlayerResponse.param1;
				
				foreach(DZLPlayerBankInfo reciver: players) {
					playerListbox.AddItem(reciver.name, reciver, 0);
				}
			
			}
		}
    }

    override Widget Init() {
        super.Init();

        payOutButton = creator.GetButtonWidget("Button_Pay_out");
        payOutButton.Show(true);
		payInButton = creator.GetButtonWidget("Button_Deposit");
		payInButton.Show(true);
		cashTransferButton = creator.GetButtonWidget("Button_Cash_Transfer");
		cashTransferButton.Show(true);

		fractionPayOutButton = creator.GetButtonWidget("Button_Pay_out_Fraction");
		fractionPayInButton = creator.GetButtonWidget("Button_Deposit_Fraction");
		fractionCashTransferButton = creator.GetButtonWidget("Button_Cash_Transfer_Fraction");

		wrapperFractionButtonCashToPlayer = creator.GetWidget("wrapper_Button_Cash_Transfer_Fraction");
        wrapperFractionButtonPayout = creator.GetWidget("wrapper_Button_Pay_out_Fraction");
        wrapperFractionButtonDeposit = creator.GetWidget("wrapper_Button_Deposit_Fraction");
        wrapperFractionCash = creator.GetWidget("wrapperFractionCash");
        wrapperFractionButtonCashToPlayer.Show(false);
        wrapperFractionButtonPayout.Show(false);
        wrapperFractionCash.Show(false);

        playerBankBalanceTextWidget = creator.GetTextWidget("DZLBank");
        playerBankBalanceTextWidget.Show(true);
        playerBalanceTextWidget = creator.GetTextWidget("DZLCash");
        playerBalanceTextWidget.Show(true);
        bankBalanceTextWidget = creator.GetTextWidget("DZLBank_Cash");
        fractionBalanceTextWidget = creator.GetTextWidget("DZLFractionCash");
        balanceTextLabelWidget = creator.GetTextWidget("Cash_at_Bank");
        bankTaxTextWidget = creator.GetTextWidget("bankTaxTextWidget");

		inputDeposit = creator.GetEditBoxWidget("Input_Deposit");
		
		playerListbox = creator.GetTextListboxWidget("Player_list");
        
		GetGame().RPCSingleParam(player, DAY_Z_LIFE_ALL_PLAYER_IDENT_DATA, null, true);

        return layoutRoot;
    }
	
	override void OnShow() {
        if (config) {
            super.OnShow();
            balanceTextLabelWidget.Show(config.bankConfig.showSumOfStoredCashInBank);
            bankBalanceTextWidget.Show(config.bankConfig.showSumOfStoredCashInBank);

            wrapperFractionCash.Show(dzlPlayer.HasFractionRightCanAccessBankAccount());
            wrapperFractionButtonDeposit.Show(dzlPlayer.HasFractionRightCanAccessBankAccount());
            wrapperFractionButtonCashToPlayer.Show(dzlPlayer.HasFractionRightCanGetMoneyFromBankAccount());
            wrapperFractionButtonPayout.Show(dzlPlayer.HasFractionRightCanGetMoneyFromBankAccount());

            UpdateGUI();
        } else {
            OnHide();
        }
    }

    override void UpdateGUI(string message = "") {
        playerBalanceTextWidget.SetText(dzlPlayer.GetMoney().ToString());
        playerBankBalanceTextWidget.SetText(dzlPlayer.GetBankMoney().ToString());

        if (player.GetBank()) {
            bankBalanceTextWidget.SetText(player.GetBank().moneyAtBank.ToString());
            bankTaxTextWidget.SetText(player.GetBank().GetTaxSum().ToString());
        }

        if (dzlPlayer.HasFractionRightCanAccessBankAccount()) {
            fractionBalanceTextWidget.SetText(dzlPlayer.GetFraction().GetBankAccount().ToString());
        }
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        if (super.OnClick(w, x, y, button)) return true;
        switch(w){
            case payInButton:
                SendDeposit(-1);
				return true;
            case payOutButton:
                SendDeposit(1);
                return true;
			case fractionPayInButton:
                SendDepositFraction(-1);
				return true;
            case fractionPayOutButton:
                SendDepositFraction(1);
                return true;
			case cashTransferButton:
			 	SendToPlayer(false);
				return true;
            case fractionCashTransferButton:
			 	SendToPlayer(true);
				return true;
			default:
				break;
        }
        return false;
    }
	
	private void SendToPlayer(bool isFraction) {
		int deposit = inputDeposit.GetText().ToInt();
		
		if (deposit < 1) {
		    player.DisplayMessage("#error_deposit_must_be_positiv");
			return;
		}
		
		int selected = playerListbox.GetSelectedRow();
		
		if (-1 == selected) {
			player.DisplayMessage("#error_no_player_was_selected");
			return;
		}
		
		DZLPlayerBankInfo playerBankInfo;

		playerListbox.GetItemData(selected, 0, playerBankInfo);
		
		if (!playerBankInfo) {
			player.DisplayMessage("#error_no_player_was_selected");
			return;
		}
		
		if (!isFraction && playerBankInfo.id == player.GetPlayerId()) {
			player.DisplayMessage("#error_you_cant_send_money_to_yourself");
			return;
		}
		
		if (deposit != 0) {
		    int money = dzlPlayer.GetAllMoney();

		    if (isFraction && dzlPlayer.HasFractionRightCanGetMoneyFromBankAccount()) {
		        money = dzlPlayer.GetFraction().GetBankAccount();
		    }

            if (deposit <= money) {
                GetGame().RPCSingleParam(player, DAY_Z_LIFE_PLAYER_DEPOSIT_TO_PLAYER, new Param3<DZLPlayerBankInfo, int, bool>(playerBankInfo, deposit, isFraction), true);
                inputDeposit.SetText("");
            } else {
                player.DisplayMessage("#error_not_enough_money_to_transfer");
            }
        } else {
            player.DisplayMessage("#error_deposit_is_not_a_int");
        }
	}


    private void SendDeposit(int factor) {
        if (inputDeposit.GetText().ToInt() >= 1) {
            int deposit = inputDeposit.GetText().ToInt();
            if ((deposit <= dzlPlayer.GetMoney() && factor == -1) || (deposit <= dzlPlayer.GetBankMoney() && factor == 1)) {
			    deposit = factor * deposit;
                GetGame().RPCSingleParam(player, DAY_Z_LIFE_PLAYER_DEPOSIT_AT_BANK_DATA, new Param2<int, bool>(deposit, false), true);
                inputDeposit.SetText("");
            } else {
                player.DisplayMessage("#error_not_enough_money_to_transfer");
            }
        } else if(inputDeposit.GetText().ToInt() <= 1){
			player.DisplayMessage("#error_deposit_must_be_positiv");
		} else {
            player.DisplayMessage("#error_deposit_is_not_a_int");
        }
	}

    private void SendDepositFraction(int factor) {
        if (inputDeposit.GetText().ToInt() >= 1) {
            int deposit = inputDeposit.GetText().ToInt();
            if ((dzlPlayer.HasFractionRightCanAccessBankAccount() && deposit <= dzlPlayer.GetMoney() && factor == -1) || (dzlPlayer.HasFractionRightCanGetMoneyFromBankAccount() && deposit <= dzlPlayer.GetFraction().GetBankAccount() && factor == 1)) {
			    deposit = factor * deposit;
                GetGame().RPCSingleParam(player, DAY_Z_LIFE_PLAYER_DEPOSIT_AT_BANK_DATA, new Param2<int, bool>(deposit, true), true);
                inputDeposit.SetText("");
            } else {
                player.DisplayMessage("#error_not_enough_money_to_transfer");
            }
        } else if(inputDeposit.GetText().ToInt() <= 1){
			player.DisplayMessage("#error_deposit_must_be_positiv");
		} else {
            player.DisplayMessage("#error_deposit_is_not_a_int");
        }
	}

}
