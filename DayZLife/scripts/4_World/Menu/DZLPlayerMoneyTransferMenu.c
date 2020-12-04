class DZLPlayerMoneyTransferMenu : DZLBaseMenu
{
    private PlayerBase receiver;
	private ButtonWidget sendMoney;
	private EditBoxWidget inputDeposit;

    void DZLPlayerMoneyTransferMenu() {
		layoutPath = "DayZLife/layout/GiveMoneyMenu/GiveMoneyMenu.layout";
        Construct();
    }

    void ~DZLPlayerMoneyTransferMenu() {
        Destruct();
    }

    void SetReceiver(PlayerBase receiver) {
        this.receiver = receiver;
    }

    override Widget Init() {
		super.Init();
		
		sendMoney = creator.GetButtonWidget("giveMoneyButton");
		inputDeposit = creator.GetEditBoxWidget("input_of_money");
		
		return layoutRoot;
    }
	
	override bool OnClick(Widget w, int x, int y, int button) {
        if (super.OnClick(w, x, y, button)) return true;

        switch(w){
            case sendMoney:
            	int deposit = inputDeposit.GetText().ToInt();
		
				if (deposit < 1) {
				    player.DisplayMessage("#error_deposit_must_be_positiv");
					return false;
				}
				
				if (-1 == receiver) {
					player.DisplayMessage("#error_no_player_was_selected");
					return false;
				}
				
				if (deposit != 0) {
		            if (deposit <= dzlPlayer.money) {
		                GetGame().RPCSingleParam(player, DAY_Z_LIFE_MONEY_TRANSFER, new Param3<PlayerBase, PlayerBase, int>(player, receiver, deposit), true);
		                inputDeposit.SetText("");
		            } else {
		                player.DisplayMessage("#error_not_enough_money_to_transfer");
		            }
		        } else {
		            player.DisplayMessage("#error_deposit_is_not_a_int");
		        }
			
                return true;
            default:
                break;
        }
        return false;
    }

    override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_MONEY_TRANSFER_RESPONSE) {
           autoptr Param1<string> paramGetResponse;
           if (ctx.Read(paramGetResponse)){
                player.DisplayMessage(paramGetResponse.param1);
                OnHide();
           }
        }
    }
}
