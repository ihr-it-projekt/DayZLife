class DZLLicenceListener: DZLBaseEventListener {

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.BUY_LICENCE) {
            Param1<string> paramBuyLicence;
            if(ctx.Read(paramBuyLicence)) {
                PlayerBase playerBuyLicence = PlayerBase.Cast(target);
                DZLPlayer dzlPlayer = playerBuyLicence.GetDZLPlayer();
                DZLCraftLicence licence = DZLConfig.Get().licenceConfig.licenceCollection.FindById(paramBuyLicence.param1);
                DZLCraftLicence depLicence;

                if(licence.dependencyLicence) {
                    depLicence = DZLConfig.Get().licenceConfig.licenceCollection.FindByName(licence.dependencyLicence);
                }

                string message = dzlPlayer.CanBuyLicence(licence, depLicence);

                if(!message) {
                    dzlPlayer.BuyLicence(licence);
                }

                g_Game.RPCSingleParam(null, DZL_RPC.EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, sender);
                g_Game.RPCSingleParam(playerBuyLicence, DZL_RPC.BUY_LICENCE_RESPONSE, new Param1<string>(message), true, sender);
            }
        } else if(rpc_type == DZL_RPC.BUY_LICENCE_USE) {
            Param1<string> paramUseLicence;
            if(ctx.Read(paramUseLicence)) {
                PlayerBase playerLicenceUse = PlayerBase.Cast(target);
                DZLCraftLicence licenceUse = DZLConfig.Get().licenceConfig.licenceCollection.FindById(paramUseLicence.param1);

                if(!licenceUse) return;

                string messageUse = playerLicenceUse.CanUseLicence(licenceUse);
                if(!messageUse) {
                    playerLicenceUse.UseLicence(licenceUse);
                    messageUse = "#item_crafted";
                }
                DZLSendMessage(sender, messageUse);
            }
        }
    }
}
