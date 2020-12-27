class DZLPlayerArrestMenu : DZLBaseMenu
{
    private PlayerBase receiver;
	private ButtonWidget setArrest;
	private EditBoxWidget inputArrest;
	private TextWidget prisonerName;

    void DZLPlayerArrestMenu() {
		layoutPath = "DayZLife/layout/Arrest/ArrestMenu.layout";
        Construct();
    }

    void ~DZLPlayerArrestMenu() {
        Destruct();
    }

    void SetReceiver(PlayerBase receiver) {
        this.receiver = receiver;
    }

    override Widget Init() {
		super.Init();
		
		setArrest = creator.GetButtonWidget("giveArrestButton");
		inputArrest = creator.GetEditBoxWidget("input_arrest");
		prisonerName = creator.GetTextWidget("prisonerName");
		return layoutRoot;
    }
	
	override void OnShow() {
		super.OnShow();
		prisonerName.SetText(receiver.GetIdentity().GetName());
	}
	
	override bool OnClick(Widget w, int x, int y, int button) {
        if (super.OnClick(w, x, y, button)) return true;

        switch(w){
            case setArrest:
            	int arrestTime = inputArrest.GetText().ToInt();
		
				if (arrestTime < 0) {
				    player.DisplayMessage("#error_arrest_time_must_be_positiv_or_null");
					return false;
				}
				
				if (!receiver) {
					player.DisplayMessage("#error_no_player_was_selected");
					return false;
				}
				
				if (arrestTime != 0) {
                    GetGame().RPCSingleParam(player, DAY_Z_LIFE_ARREST_PLAYER, new Param3<PlayerBase, PlayerBase, int>(player, receiver, arrestTime), true);
                    inputArrest.SetText("");
		        } else {
		            player.DisplayMessage("#error_arrest_time_is_not_a_int");
		        }
			
                return true;
            default:
                break;
        }
        return false;
    }

    override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_ARREST_PLAYER_RESPONSE) {
           autoptr Param1<string> paramGetResponse;
           if (ctx.Read(paramGetResponse)){
                OnHide();
           }
        }
    }
}
