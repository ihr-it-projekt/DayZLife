class DZLPlayerTicketListener
{
    void DZLPlayerTicketListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLPlayerTicketListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_CREATE_TICKET) {
            autoptr Param3<PlayerBase, int, string> paramCreateTicket;
            if (ctx.Read(paramCreateTicket)){
                PlayerBase cop = PlayerBase.Cast(target);
                PlayerBase ticketReceiver = paramCreateTicket.param1;
                int ticketValue = paramCreateTicket.param2;
                string ticketReason = paramCreateTicket.param3;
				
				DZLPlayer copDzl = cop.GetDZLPlayer();
				DZLPlayer prisonerDzl = ticketReceiver.GetDZLPlayer();
				
				if(!copDzl.IsActiveAsCop()) return;
				if(!DAY_Z_LIFE_DEBUG && prisonerDzl.IsActiveAsCop()) return;
				
				prisonerDzl.AddTicket(ticketValue, ticketReason);

				GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, ticketReceiver.GetIdentity());
                GetGame().RPCSingleParam(null, DAY_Z_LIFE_CREATE_TICKET_RESPONSE, null, true, sender);
				DZLSendMessage(ticketReceiver.GetIdentity(), "#you_got_a_ticket: " + ticketValue.ToString() + " $");
				DZLSendMessage(cop.GetIdentity(), "#you_gave_a_player_a_ticket: " + ticketValue.ToString());
				DZLLogTicket(ticketReceiver.GetPlayerId(), "got a ticket", ticketValue);
            }
        } else if (rpc_type == DAY_Z_LIFE_PAY_TICKET) {
			autoptr Param1<string> paramPayTicket;
			if (ctx.Read(paramPayTicket)){
				PlayerBase playerWhoPay = PlayerBase.Cast(target);
				DZLPlayer dzlPayerWhoPay = playerWhoPay.GetDZLPlayer();
				DZLTicket ticket = dzlPayerWhoPay.GetTicketById(paramPayTicket.param1);

				if (ticket && dzlPayerWhoPay.HasEnoughMoney(ticket.value)) {
					dzlPayerWhoPay.AddMoneyToPlayer(ticket.value * -1);
					GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, playerWhoPay.GetIdentity());
					DZLSendMessage(playerWhoPay.GetIdentity(), "#ticket_was_paid");
					DZLLogTicket(playerWhoPay.GetPlayerId(), "pay a ticket", ticketValue);
					DZLDatabaseLayer.Get().GetBank().AddTax(ticket.value);
					dzlPayerWhoPay.RemoveTicketById(ticket.GetId());
				}
			}
	   }
    }
}
