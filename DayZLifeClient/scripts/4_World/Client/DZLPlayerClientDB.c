class DZLPlayerClientDB: DZLBaseEventListener {
    private static ref DZLPlayerClientDB db;

    private ref DZLConfig config;
    private ref DZLPlayer dzlPlayer;
    private ref DZLBank dzlBank;

    static DZLPlayerClientDB Get() {
        if(!db) {
            db = new DZLPlayerClientDB;
            GetGame().RPCSingleParam(DZLPlayerBaseHelper.GetPlayer(), DZL_RPC.EVENT_GET_CONFIG, null, true);
            GetGame().RPCSingleParam(DZLPlayerBaseHelper.GetPlayer(), DZL_RPC.PLAYER_BANK_DATA, null, true);
            GetGame().RPCSingleParam(DZLPlayerBaseHelper.GetPlayer(), DZL_RPC.PLAYER_DATA, null, true);
        }
        return db;
    }

    DZLBank GetBank() {
        if(!dzlBank) GetGame().RPCSingleParam(DZLPlayerBaseHelper.GetPlayer(), DZL_RPC.PLAYER_BANK_DATA, null, true);

        return dzlBank;
    }

    DZLPlayer GetDZLPlayer() {
        if(!dzlPlayer) GetGame().RPCSingleParam(DZLPlayerBaseHelper.GetPlayer(), DZL_RPC.PLAYER_DATA, null, true);

        return dzlPlayer;
    }

    void SetDZLPlayer(DZLPlayer _dzlPlayer, string playerId) {
        if(_dzlPlayer.dayZPlayerId != playerId) return;
        this.dzlPlayer = _dzlPlayer;
    }

    void RequestUpdateDZLPlayer() {
        GetGame().RPCSingleParam(DZLPlayerBaseHelper.GetPlayer(), DZL_RPC.PLAYER_DATA, null, true);
        GetGame().RPCSingleParam(DZLPlayerBaseHelper.GetPlayer(), DZL_RPC.PLAYER_BANK_DATA, null, true);
    }

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        PlayerBase player = DZLPlayerBaseHelper.GetPlayer();
        if(!player) return;
        if(rpc_type == DZL_RPC.PLAYER_DATA_RESPONSE) {
            Param1 <ref DZLPlayer> dzlPlayerParam;
            if(ctx.Read(dzlPlayerParam) && dzlPlayerParam.param1) {
                SetDZLPlayer(dzlPlayerParam.param1, player.GetPlayerId());
                player.UpdatePlayerAtDependencies();
            }
        } else if(rpc_type == DZL_RPC.PLAYER_BANK_DATA_RESPONSE) {
            Param1 <ref DZLBank> dzlBankParam;
            if(ctx.Read(dzlBankParam) && dzlBankParam.param1) {
                dzlBank = dzlBankParam.param1;
            }
        } else if(rpc_type == DZL_RPC.EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE) {
            RequestUpdateDZLPlayer();
        }
    }
}