
modded class CarScript
{
    string lastDriverId = "";
    bool isSold = false;
	int dzlCarId = 0;
    ref array<string> playerAccess;
    string ownerId;
   
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
        SynchronizeValues();
    }

    void AddOwner(PlayerIdentity player) {
        ownerId = player.GetId();
        playerAccess = new array<string>;
        SynchronizeValues();
    }

    bool IsOwner(PlayerIdentity player) {
        if(GetGame().IsServer() && ownerId == "") {
            ownerId = player.GetId();
        }
        
        return ownerId == player.GetId();
    }

	override void EEInit() {
        super.EEInit();

        if(dzlCarId == 0) {
            dzlCarId = Math.RandomIntInclusive(1, int.MAX - 1);
        }

        playerAccess = new array<string>;

        SynchronizeValues();
    }

    void UpdatePlayerAccess(array<string> playerAccess) {
        this.playerAccess = playerAccess;
        SynchronizeValues();
    }

    bool HasPlayerAccess(string ident) {
    	DebugMessageDZL("ownerId" + ownerId);
    	DebugMessageDZL("ident" + ident);
        return ident == ownerId || -1 != playerAccess.Find(ident);
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

        Param3<int, ref array<string>, string> store = new Param3<int, ref array<string>, string>(dzlCarId, playerAccess, ownerId);
        ctx.Write(store);
	}

	override bool IsInventoryVisible(){
        return (GetGame().GetPlayer() && (!GetGame().GetPlayer().GetCommand_Vehicle() || GetGame().GetPlayer().GetCommand_Vehicle().GetTransport() == this)) && HasPlayerAccess(GetGame().GetPlayer().GetIdentity().GetId());
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
        DebugMessageDZL("load ownerId" + ownerId);
        DebugMessageDZL("load dzlCarId" + dzlCarId);

        SynchronizeValues();

		return true;
	}



	void SynchronizeValues() {
        if (GetGame().IsServer()) {
            SetSynchDirty();
        }
    }
}
