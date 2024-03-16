modded class PlayerBase {
    override bool OnStoreLoad(ParamsReadContext ctx, int version) {
        bool isOkay = super.OnStoreLoad(ctx, version);
        if(!isOkay) return false;

        dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(GetPlayerId());
        if(dzlPlayer) dzlPlayer.player = this;

        return true;
    }

    override void OnStoreSave(ParamsWriteContext ctx) {
        super.OnStoreSave(ctx);
        dzlPlayer.Save();
    }
}