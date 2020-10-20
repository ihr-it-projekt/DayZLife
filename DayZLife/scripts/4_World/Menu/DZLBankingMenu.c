class DZLBankingMenu : UIScriptedMenu
{
    private ref DZLUIItemCreator creator;
	private ref DZLConfig config;


    ButtonWidget closeButton;
    ButtonWidget payInButton;
    ButtonWidget payOutButton;
	
    TextWidget balanceTextWidget;
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
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void SetConfig(ref DZLConfig config) {
        this.config = config;
    }

    void UpdateGUI(string message = "") {
        if(message) errorMessageTextWidget.SetText(message);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE) {
            autoptr Param1<ref DZLBank> paramGetBankData;
            if (ctx.Read(paramGetBankData)){
                bankBalanceTextWidget.SetText(paramGetBankData.param1.moneyAtBank.ToString());
            }
        } else if (rpc_type == DAY_Z_LIFE_PLAYER_DATA_RESPONSE) {
           autoptr Param1<ref DZLPlayer> paramGetPlayerData;
           if (ctx.Read(paramGetPlayerData)){
                playerBalanceTextWidget.SetText(paramGetPlayerData.param1.money.ToString());
                bankBalanceTextWidget.SetText(paramGetPlayerData.param1.bank.ToString());
           }
       } else if (rpc_type == DAY_Z_LIFE_PLAYER_DEPOSIT_AT_BANK_DATA_RESPONSE) {
           autoptr Param1<string> paramGetResponse;
           if (ctx.Read(paramGetResponse)){
                errorMessageTextWidget.SetText(paramGetResponse.param1);
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

        balanceTextWidget = creator.GetTextWidget("DZLBank");
        balanceTextWidget.Show(true);
        playerBalanceTextWidget = creator.GetTextWidget("DZLCash");
        playerBalanceTextWidget.Show(true);
        bankBalanceTextWidget = creator.GetTextWidget("DZLBank_Cash");
        balanceTextLabelWidget = creator.GetTextWidget("Cash_at_Bank");
		
		inputDeposit = creator.GetEditBoxWidget("Input_Deposit");
        
		errorMessageTextWidget = creator.GetTextWidget("Error_Message");
        
        layoutRoot = creator.GetLayoutRoot();

        layoutRoot.Show(false);

        return layoutRoot;
    }
	
	override void OnShow() {
        if (config) {
            super.OnShow();
            errorMessageTextWidget.SetText("");
            playerBalanceTextWidget.SetText(PlayerBaseHelper.GetPlayer().dzlPlayer.money.ToString());
            balanceTextWidget.SetText(PlayerBaseHelper.GetPlayer().dzlPlayer.bank.ToString());

			balanceTextLabelWidget.Show(config.bankConfig.showSumOfStoredCashInBank);
			bankBalanceTextWidget.Show(config.bankConfig.showSumOfStoredCashInBank);

			PlayerBase player = PlayerBaseHelper.GetPlayer();
			bankBalanceTextWidget.SetText(player.dzlBank.moneyAtBank.ToString());

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
        }
        return false;
    }


    private bool SendDeposit(int factor) {
        float deposit = factor * inputDeposit.GetText().ToFloat();

        if (deposit != 0) {
            if (deposit > PlayerBaseHelper.GetPlayer().dzlPlayer.money || deposit < PlayerBaseHelper.GetPlayer().dzlPlayer.bank) {
                GetGame().RPCSingleParam(PlayerBaseHelper.GetPlayer(), DAY_Z_LIFE_PLAYER_DEPOSIT_AT_BANK_DATA, new Param2<PlayerBase, float>(PlayerBaseHelper.GetPlayer(), deposit), true);
                errorMessageTextWidget.SetText("");
            } else {
                errorMessageTextWidget.SetText("#error_not_enough_money_to_transfer");
            }
        } else {
            errorMessageTextWidget.SetText("#error_deposit_is_not_a_float");
        }
        return true;

    }

}