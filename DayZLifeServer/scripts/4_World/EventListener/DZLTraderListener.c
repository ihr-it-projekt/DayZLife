class DZLTraderListener: DZLBaseEventListener {

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.TRADE_ACTION) {
            Param3<ref array<string>, ref array<EntityAI>, ref DZLTraderPosition> paramTrade;
            if(!ctx.Read(paramTrade)) return;

            DZLTradeObject tradeObject = new DZLTradeObject(PlayerBase.Cast(target), paramTrade.param2, paramTrade.param1, paramTrade.param3);

            tradeObject.CheckCategories();
            if(!tradeObject.CanTrade()) return;

            tradeObject.Trade();
            tradeObject.SaveStorage();
            tradeObject.LogTrades();
            tradeObject.SendTraderResponse();
        } else if(rpc_type == DZL_RPC.EVENT_GET_CONFIG_TRADER_STORAGE) {
            GetGame().RPCSingleParam(target, DZL_RPC.EVENT_GET_CONFIG_TRADER_STORAGE_RESPONSE, new Param1<ref array<ref DZLTraderTypeStorage>>(DZLDatabaseLayer.Get().GetTraderStorage().GetStorageItems()), true, sender);
        }
    }
}
