class DZLConfigListener: DZLBaseEventListener {

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.PLAYER_DATA) {
            DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(sender.GetId());;
            dzlPlayer.UpdateName(sender.GetName());
            dzlPlayer.GetFractionMember();
            GetGame().RPCSingleParam(target, DZL_RPC.PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(dzlPlayer), true, sender);
        }
    }
}
