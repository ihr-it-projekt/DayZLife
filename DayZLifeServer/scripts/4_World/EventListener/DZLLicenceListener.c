class DZLLicenceListener
{
    ref DZLConfig config;

    void DZLLicenceListener() {
        config = DZLConfig.Get();
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLLicenceListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
		if (!DZLLicenceCheck.Get().HasActiveLicence(sender)) return;
        if (rpc_type == DAY_Z_LIFE_BUY_LICENCE) {
            autoptr Param2<PlayerBase, string> paramBuyLicence;
            if (ctx.Read(paramBuyLicence)){
                DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(sender.GetId());
				DZLLicence licence = config.licenceConfig.licences.FindById(paramBuyLicence.param2);
				DZLLicence depLicence;

				if (licence.dependencyLicence) {
					depLicence = config.licenceConfig.licences.FindByName(licence.dependencyLicence);
				}

                string message = dzlPlayer.CanBuyLicence(licence, depLicence);

                if(!message){
                    dzlPlayer.BuyLicence(licence);
                }
				
				GetGame().RPCSingleParam(paramBuyLicence.param1, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(dzlPlayer), true, sender);
				GetGame().RPCSingleParam(paramBuyLicence.param1, DAY_Z_LIFE_BUY_LICENCE_RESPONSE, new Param1<string>(message), true, sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_BUY_LICENCE_USE) {
            autoptr Param2<PlayerBase, string> paramUseLicence;
            if (ctx.Read(paramUseLicence)){
                DZLPlayer dzlPlayerUse = DZLDatabaseLayer.Get().GetPlayer(sender.GetId());
                DZLLicence licenceUse = config.licenceConfig.licences.FindById(paramUseLicence.param2);

                if (!licenceUse) return;

                string messageUse = paramUseLicence.param1.CanUseLicence(licenceUse);
                if (!messageUse) {
                    paramUseLicence.param1.UseLicence(licenceUse);
                    messageUse = "#item_crafted";
                }
                DZLSendMessage(sender, messageUse);
            }
        }
    }
}
