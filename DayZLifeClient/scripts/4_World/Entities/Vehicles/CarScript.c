modded class CarScript {
    string lastDriverId = "";
    string ownerId = "";
    string ownerName = "";

    ref array<string> playerAccess = new array<string>;
    int dzlCarId = Math.RandomIntInclusive(1, int.MAX - 1);
    bool isSold = false;
    bool isRaided = false;
    bool hasInsurance = false;

    void CarScript() {
        RegisterNetSyncVariableInt("dzlCarId");
        RegisterNetSyncVariableBool("isSold");
        RegisterNetSyncVariableBool("isRaided");
        RegisterNetSyncVariableBool("hasInsurance");
    }

    override void EEInit() {
        super.EEInit();

        RPCSingleParam(DZL_RPC.REQUEST_UPDATE_CAR, null, true);

        SetAllowDamage(true);
    }

    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx) {
        super.OnRPC(sender, rpc_type, ctx);

        switch(rpc_type) {
            case(DZL_RPC.UPDATE_CAR_LAST_DRIVER): {
                Param1<string> dataLastDriver;
                if(!ctx.Read(dataLastDriver)) return;

                lastDriverId = dataLastDriver.param1;
                return;
            }
            case(DZL_RPC.UPDATE_CAR): {
                Param3<ref array<string>, string, string> updateData;
                if(!ctx.Read(updateData)) return;

                playerAccess = updateData.param1;
                ownerId = updateData.param2;
                ownerName = updateData.param3;
                return;
            }
            case(DZL_RPC.UPDATE_CAR_ACCESS): {
                Param1<ref array<string>> data;
                if(!ctx.Read(data)) return;

                playerAccess = data.param1;
                return;
            }
            case(DZL_RPC.UPDATE_CAR_OWNER): {
                Param2<string, string> dataOwner;
                if(!ctx.Read(data)) return;

                ownerId = dataOwner.param1;
                ownerName = dataOwner.param2;
                return;
            }
            default: {
                return;
            }
        }
    }

    override void SetActions() {
        super.SetActions();

        AddAction(DZLActionOpenCarMenu);
        AddAction(DZLActionGetOwnerName);
        AddAction(DZLActionGetInsurance);
        AddAction(DZLActionRaidCar);
    }

    bool IsOwner(PlayerIdentity player) {
        return ownerId == player.GetId();
    }

    bool HasPlayerAccess(PlayerBase player) {
        if(!player) return false;

        string ident = player.GetPlayerId();
        DZLPlayer dzlPlayer = player.GetDZLPlayer();
        if(!dzlPlayer) return false;

        if(isRaided) return true;
        if(ident == ownerId) return true;
        if(-1 != playerAccess.Find(ident)) return true;
        if(dzlPlayer.IsActiveJob(DAY_Z_LIFE_JOB_COP)) return true;
        if(dzlPlayer.IsActiveJob(DAY_Z_LIFE_JOB_ARMY)) return true;
        if(DZLConfig.Get().adminIds.HasAccess(DAY_Z_LIFE_ACCESS_CARS, ident)) return true;

        return false;
    }

    array<string> GetPlayerAccess() {
        return playerAccess;
    }

    bool CanOpenDoor(PlayerBase player) {
        return HasPlayerAccess(player);
    }

    bool CanRaidDoor(PlayerBase player) {
        return !HasPlayerAccess(player);
    }

    override bool IsInventoryVisible() {
        PlayerBase player = DZLPlayerBaseHelper.GetPlayer();

        return super.IsInventoryVisible() && HasPlayerAccess(player);
    }
}
