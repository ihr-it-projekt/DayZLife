
modded class CarScript
{
    string lastDriverId = "";
    bool isSold = false;
	int dzlCarId = 0;
    ref array<string> playerAccess;
    PlayerIdentity owner;
   
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
        owner = null;
        playerAccess = new array<string>;
        SynchronizeValues();
    }

    void AddOwner(PlayerIdentity player) {
        owner = player;
        playerAccess = new array<string>;
        SynchronizeValues();
    }

    bool IsOwner(PlayerIdentity playerId) {
        return owner.GetId() == playerId;
    }

	override void EEInit() {
        super.EEInit();

        if(dzlCarId == 0) {
            dzlCarId = Math.RandomIntInclusive(1, int.MAX - 1);
        }

        SynchronizeValues();
    }

    void UpdatePlayerAccess(array<string> playerAccess) {
        this.playerAccess = playerAccess;
        SynchronizeValues();
    }

    bool HasPlayerAccess(string ident) {
    	DebugMessageDZL("owner" + owner);
    	DebugMessageDZL("ident" + ident);
        return ident == owner.GetId() || -1 != playerAccess.Find(ident);
    }

    void RemovePlayerAccess(string ident) {
        int index = playerAccess.Find(ident);
        if (index != -1) {
            playerAccess.Remove(index);
            SynchronizeValues();
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

        Param3<int, ref array<string>, PlayerIdentity> store = new Param3<int, ref array<string>, PlayerIdentity>(dzlCarId, playerAccess, owner);
        ctx.Write(store);
	}

	override bool IsInventoryVisible(){
        return (GetGame().GetPlayer() && (!GetGame().GetPlayer().GetCommand_Vehicle() || GetGame().GetPlayer().GetCommand_Vehicle().GetTransport() == this)) && HasPlayerAccess(GetGame().GetPlayer().GetIdentity().GetId());
    }

	override bool OnStoreLoad(ParamsReadContext ctx, int version){
		if (!super.OnStoreLoad( ctx, version))
			return false;

        Param3<int, ref array<string>, PlayerIdentity> store = new Param3<int, ref array<string>, PlayerIdentity>(0, new array<string>, null);
        if (ctx.Read(store)){
            dzlCarId = store.param1;
            playerAccess = store.param2;
            owner = store.param3;
        }

        SynchronizeValues();

		return true;
	}



	void SynchronizeValues() {
        if (GetGame().IsServer()) {
            SetSynchDirty();
        }
    }
}
