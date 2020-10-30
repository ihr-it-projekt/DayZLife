class DZLLicenceListener
{
    ref DZLConfig config;

    void DZLLicenceListener() {
        config = new DZLConfig;
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLLicenceListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_BUY_LICENCE) {
            autoptr Param2<PlayerBase, int> paramBuyLicence;
            if (ctx.Read(paramBuyLicence)){
                DZLPlayer dzlPlayer = new DZLPlayer(sender.GetId());
				
				DZLLicence licence = config.licenceConfig.licences.Get(paramBuyLicence.param2);

                string message = dzlPlayer.CanBuyLicence(licence);

                if("" == message){
                    dzlPlayer.BuyLicence(licence);
                }
				
				GetGame().RPCSingleParam(paramBuyLicence.param1, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(new DZLPlayer(sender.GetId())), true, sender);
				GetGame().RPCSingleParam(paramBuyLicence.param1, DAY_Z_LIFE_BUY_LICENCE_RESPONSE, new Param1<string>(message), true, sender);
            }
        }
    }
}