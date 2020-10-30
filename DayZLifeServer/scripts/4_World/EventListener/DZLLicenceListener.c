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
            autoptr Param2<PlayerBase, ref DZLLicence> paramBuyLicence;
            if (ctx.Read(paramBuyLicence)){
                DZLPlayer dzlPlayer = new DZLPlayer(sender.GetId());

                string message = dzlPlayer.CanBuyLicence(paramBuyLicence.param2);

                if("" == message){
                    dzlPlayer.BuyLicence(paramBuyLicence.param2);
                }
				
				dzlPlayer = new DZLPlayer(sender.GetId());

                GetGame().RPCSingleParam(paramBuyLicence.param1, DAY_Z_LIFE_BUY_LICENCE_RESPONSE, new Param2<ref DZLPlayer, string>(dzlPlayer, message), true, sender);
				GetGame().RPCSingleParam(paramBuyLicence.param1, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(dzlPlayer), true, sender);
            }
        }
    }
}