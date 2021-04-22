class DZLOpenTicketPlayer
{
    int valueOfTickets;
    int countOfTickets;
    string name;

    void DZLOpenTicketPlayer(PlayerBase player) {
        this.name = player.GetIdentity().GetName();

        array<ref DZLTicket> tickets = player.GetDZLPlayer().GetTickets();
        countOfTickets = ticket.Count();

        foreach(DZLTicket ticket: tickets) {
        	valueOfTickets += ticket.value;
        }
    }
}
