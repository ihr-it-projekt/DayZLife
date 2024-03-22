class DZLPlayerArrestMenu : DZLBaseMenu {
    private PlayerBase receiver;
    private ButtonWidget setArrest;
    private EditBoxWidget inputArrest;
    private EditBoxWidget inputArrestReason;
    private TextWidget prisonerName;

    void DZLPlayerArrestMenu() {
        layoutPath = "DayZLifeClient/layout/Arrest/ArrestMenu.layout";
    }

    void SetReceiver(PlayerBase _receiver) {
        this.receiver = _receiver;
    }

    override Widget Init() {
        super.Init();

        setArrest = creator.GetButtonWidget("giveArrestButton");
        inputArrest = creator.GetEditBoxWidget("input_arrest");
        inputArrestReason = creator.GetEditBoxWidget("arrest_reason");
        prisonerName = creator.GetTextWidget("prisonerName");
        return layoutRoot;
    }

    override void OnShow() {
        super.OnShow();
        prisonerName.SetText(receiver.GetIdentity().GetName());
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        if(super.OnClick(w, x, y, button)) return true;

        switch(w) {
            case setArrest:
                int arrestTime = inputArrest.GetText().ToInt();
                string arrestReason = inputArrestReason.GetText();

                if(arrestTime < 0) {
                    player.DisplayMessage("#error_arrest_time_must_be_positiv_or_null");
                    return false;
                }

                if(!receiver) {
                    player.DisplayMessage("#error_no_player_was_selected");
                    return false;
                }

                if(arrestTime != 0) {
                    GetGame().RPCSingleParam(player, DZL_RPC.ARREST_PLAYER, new Param3<PlayerBase, int, string>(receiver, arrestTime, arrestReason), true);
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
        if(rpc_type == DZL_RPC.ARREST_PLAYER_RESPONSE) {
            OnHide();
        }
    }
}
