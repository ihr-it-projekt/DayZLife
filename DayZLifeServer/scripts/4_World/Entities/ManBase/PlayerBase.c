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

    override DZLBank GetBank() {
        return DZLDatabaseLayer.Get().GetBank();
    }

    void Reload() {
        dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(GetPlayerId());
        if(dzlPlayer) dzlPlayer.player = this;
    }

    void TransferFromDeadPlayer(DZLPlayer playerTarget) {
        playerTarget.AddMoneyToPlayer(moneyPlayerIsDead);
        moneyPlayerIsDead = 0;
    }
}