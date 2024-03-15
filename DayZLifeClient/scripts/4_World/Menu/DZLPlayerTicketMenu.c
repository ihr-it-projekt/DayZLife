class DZLPlayerTicketMenu : DZLBaseMenu {
    private PlayerBase receiver;
    private ButtonWidget createTicket;
    private EditBoxWidget inputTicket;
    private EditBoxWidget inputTicketReason;
    private TextWidget prisonerName;

    void DZLPlayerTicketMenu() {
        layoutPath = "DayZLifeClient/layout/Ticket/TicketMenu.layout";
        Construct();
    }

    void ~DZLPlayerTicketMenu() {
        Destruct();
    }

    void SetReceiver(PlayerBase _receiver) {
        this.receiver = _receiver;
    }

    override Widget Init() {
        super.Init();

        createTicket = creator.GetButtonWidget("createTicketButton");
        inputTicket = creator.GetEditBoxWidget("input_ticket");
        inputTicketReason = creator.GetEditBoxWidget("ticket_reason");
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
            case createTicket:
                int ticketValue = inputTicket.GetText().ToInt();
                string ticketReason = inputTicketReason.GetText();

                if(ticketValue < 0) {
                    player.DisplayMessage("#error_value_must_be_positiv_or_null");
                    return false;
                }

                if(!receiver) {
                    player.DisplayMessage("#error_no_player_was_selected");
                    return false;
                }

                if(ticketValue != 0) {
                    GetGame().RPCSingleParam(player, DZL_RPC.CREATE_TICKET, new Param3<PlayerBase, int, string>(receiver, ticketValue, ticketReason), true);
                    inputTicket.SetText("");
                    inputTicketReason.SetText("");
                } else {
                    player.DisplayMessage("#error_value_is_not_a_int");
                }

                return true;
            default:
                break;
        }
        return false;
    }

    override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.CREATE_TICKET_RESPONSE) {
            OnHide();
        }
    }
}
