
modded class CarScript
{
    string lastDriverId = "";
    bool isSold = false;
	int dzlCarId = 0;
    ref array<string> playerAccess;
    string ownerId;
    bool isSync = false;

    override void OnEngineStart() {
        super.OnEngineStart();
        Human player = CrewMember(DayZPlayerConstants.VEHICLESEAT_DRIVER);
        if (player) {
            lastDriverId = player.GetIdentity().GetId();
        }
	}

	override void SetActions(){
	    super.SetActions();

        AddAction(DZLActionOpenCarMenu);
	}

	void RemoveOwner() {
        ownerId = "";
        playerAccess = new array<string>;
        SynchronizeValues(null);
    }

    void AddOwner(PlayerIdentity player) {
        ownerId = player.GetId();
        playerAccess = new array<string>;
        SynchronizeValues(null);
    }

    bool IsOwner(PlayerIdentity player) {
        if(GetGame().IsServer() && ownerId == "") {
            ownerId = player.GetId();
            SynchronizeValues(null);
        }
        
        return ownerId == player.GetId();
    }

	override void EEInit() {
        super.EEInit();

        if(dzlCarId == 0) {
            dzlCarId = Math.RandomIntInclusive(1, int.MAX - 1);
        }
        playerAccess = new array<string>;

        SynchronizeValues(null);
    }

    void UpdatePlayerAccess(array<string> playerAccess) {
        this.playerAccess = playerAccess;
        SynchronizeValues(null);
    }

    bool HasPlayerAccess(string ident) {
    	if (GetGame().IsClient() && !isSync) {
    	    GetGame().RPCSingleParam(GetGame().GetPlayer(), DAY_Z_LIFE_UPDATE_CAR_FROM_PLAYER_SIDE, new Param1<CarScript>(this), true);
    	    isSync = true;
    	}

        return ident == ownerId || -1 != playerAccess.Find(ident);
    }

    void RemovePlayerAccess(string ident) {
        int index = playerAccess.Find(ident);
        if (index != -1) {
            playerAccess.Remove(index);
            SynchronizeValues(null);
        }
    }

    array<string> GetPlayerAccess() {
        return playerAccess;
    }

    bool CanOpenDoor(PlayerBase player) {
        return HasPlayerAccess(player.GetIdentity().GetId());
    }

    bool CanLookDoor(PlayerBase player, int index) {
        return HasPlayerAccess(player.GetIdentity().GetId());
    }

    bool CanRaidDoor(PlayerBase player, int index) {
        return !HasPlayerAccess(player.GetIdentity().GetId());
    }

    override void OnStoreSave(ParamsWriteContext ctx){
		super.OnStoreSave(ctx);

        Param3<int, ref array<string>, string> store = new Param3<int, ref array<string>, string>(dzlCarId, playerAccess, ownerId);
        ctx.Write(store);
	}

	override bool IsInventoryVisible() {
	    PlayerBase player = PlayerBaseHelper.GetPlayer();
	    
	    return super.IsInventoryVisible() && (HasPlayerAccess(player.GetIdentity().GetId()) || player.dzlPlayer.IsActiveAsCop());
    }

	override bool OnStoreLoad(ParamsReadContext ctx, int version){
		if (!super.OnStoreLoad( ctx, version))
			return false;

        Param3<int, ref array<string>, string> store = new Param3<int, ref array<string>, string>(0, new array<string>, "");
        if (ctx.Read(store)){
            dzlCarId = store.param1;
            playerAccess = store.param2;
            ownerId = store.param3;
        }

        SynchronizeValues(null);
		return true;
	}

	void SynchronizeValues(PlayerIdentity sender) {
        GetGame().RPCSingleParam(this, DAY_Z_LIFE_UPDATE_CAR, new Param4<CarScript, int, ref array<string>, string>(this, dzlCarId, playerAccess, ownerId), true, sender);
    }
}
