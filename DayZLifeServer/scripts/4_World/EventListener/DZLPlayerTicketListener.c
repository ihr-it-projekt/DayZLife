class DZLPlayerTicketListener: DZLBaseEventListener {

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.CREATE_TICKET) {
            Param3<PlayerBase, int, string> paramCreateTicket;
            if(ctx.Read(paramCreateTicket)) {
                PlayerBase cop = PlayerBase.Cast(target);
                PlayerBase ticketReceiver = paramCreateTicket.param1;
                int ticketValue = paramCreateTicket.param2;
                string ticketReason = paramCreateTicket.param3;

                DZLPlayer copDzl = cop.GetDZLPlayer();
                DZLPlayer prisonerDzl = ticketReceiver.GetDZLPlayer();

                if(!copDzl.IsActiveJob(DAY_Z_LIFE_JOB_COP)) return;
                if(prisonerDzl.IsActiveJob(DAY_Z_LIFE_JOB_COP)) return;

                prisonerDzl.AddTicket(ticketValue, ticketReason);

                g_Game.RPCSingleParam(null, DZL_RPC.EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, ticketReceiver.GetIdentity());
                g_Game.RPCSingleParam(null, DZL_RPC.CREATE_TICKET_RESPONSE, null, true, sender);
                DZLSendMessage(ticketReceiver.GetIdentity(), "#you_got_a_ticket: " + ticketValue.ToString() + " $");
                DZLSendMessage(cop.GetIdentity(), "#you_gave_a_player_a_ticket: " + ticketValue.ToString());
                DZLLogTicket(ticketReceiver.GetPlayerId(), "got a ticket", ticketValue);
            }
        } else if(rpc_type == DZL_RPC.PAY_TICKET) {
            Param1<string> paramPayTicket;
            if(ctx.Read(paramPayTicket)) {
                PlayerBase playerWhoPay = PlayerBase.Cast(target);
                DZLPlayer dzlPayerWhoPay = playerWhoPay.GetDZLPlayer();
                DZLTicket ticket = dzlPayerWhoPay.GetTicketById(paramPayTicket.param1);

                if(ticket && dzlPayerWhoPay.HasEnoughMoney(ticket.value)) {
                    dzlPayerWhoPay.AddMoneyToPlayer(ticket.value * -1);
                    g_Game.RPCSingleParam(null, DZL_RPC.EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, playerWhoPay.GetIdentity());
                    DZLSendMessage(playerWhoPay.GetIdentity(), "#ticket_was_paid");
                    DZLLogTicket(playerWhoPay.GetPlayerId(), "pay a ticket", ticketValue);
                    DZLDatabaseLayer.Get().GetBank().AddTax(ticket.value);
                    dzlPayerWhoPay.RemoveTicketById(ticket.GetId());
                }
            }
        }
    }
}
