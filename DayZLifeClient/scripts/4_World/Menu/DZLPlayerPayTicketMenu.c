class DZLPlayerPayTicketMenu: DZLBaseMenu {
    private ButtonWidget payTicket;
    private TextListboxWidget openTicketsList

    void DZLPlayerPayTicketMenu() {
        layoutPath = "DayZLifeClient/layout/Ticket/TicketPayMenu.layout";
        Construct();
    }

    void ~DZLPlayerPayTicketMenu() {
        Destruct();
    }

    override Widget Init() {
        super.Init();

        payTicket = creator.GetButtonWidget("payTicketButton");
        openTicketsList = creator.GetTextListboxWidget("openTicketsList");
        return layoutRoot;
    }

    override void OnShow() {
        super.OnShow();
        UpdateTickets();
    }

    override void UpdateGUI(string message = "") {
        super.UpdateGUI(message);
        UpdateTickets();
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        if (super.OnClick(w, x, y, button)) return true;

        switch(w) {
        case payTicket:
            int index = openTicketsList.GetSelectedRow();

            if (-1 == index) {
                player.DisplayMessage("#no_ticket_selected");
                return true;
            }

            DZLTicket ticketPay = null;
            openTicketsList.GetItemData(index, 0, ticketPay);

            if (ticketPay) {
                if (dzlPlayer.HasEnoughMoney(ticketPay.value)) {
                    GetGame().RPCSingleParam(player, DAY_Z_LIFE_PAY_TICKET, new Param1<string>(ticketPay.GetId()), true);
                } else {
                    player.DisplayMessage("#error_not_enough_money");
                }
            }

            return true;
        default:
            break;
        }
        return false;
    }

    void UpdateTickets() {
        openTicketsList.ClearItems();
        array<ref DZLTicket> tickets = dzlPlayer.GetTickets();
        foreach(DZLTicket ticket: tickets) {
            int pos = openTicketsList.AddItem(ticket.reason, ticket, 0);
            openTicketsList.SetItem(pos, ticket.value.ToString() + " $", ticket, 1);
            openTicketsList.SetItem(pos, ticket.creationDate.ToDateString(), ticket, 2);
        }
    }
}
