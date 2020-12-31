modded class CarScript
{
    string lastDriverId = "";
    bool isSold = false;
	int dzlCarId = 0;
    ref array<string> playerAccess;
    string ownerId = "";
    string ownerName = "";
    bool isSync = false;
    private int timeAskForDataSync;

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
        AddAction(ActionGetOwnerName);
	}

	void RemoveOwner() {
        ownerId = "";
        ownerName = "";

        playerAccess = new array<string>;
        SynchronizeValues(null);
    }

    void AddOwner(PlayerIdentity player) {
        ownerId = player.GetId();
        ownerName = player.GetName();
        playerAccess = new array<string>;
        SynchronizeValues(null);
    }

    bool IsOwner(PlayerIdentity player) {
        if(GetGame().IsServer() && ownerId == "") {
            ownerId = player.GetId();
            ownerName = player.GetName();
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

    bool HasPlayerAccess(PlayerBase player) {
        DZLDate currentDate = new DZLDate();
    	if (GetGame().IsClient() && currentDate.inSeconds - timeAskForDataSync > 5 && !isSync) {
    	    GetGame().RPCSingleParam(GetGame().GetPlayer(), DAY_Z_LIFE_UPDATE_CAR_FROM_PLAYER_SIDE, new Param1<CarScript>(this), true);
			timeAskForDataSync = currentDate.inSeconds;
    	}

    	string ident = player.GetIdentity().GetId();

        return ident == ownerId || -1 != playerAccess.Find(ident) || player.dzlPlayer.IsActiveAsCop();
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
        return HasPlayerAccess(player);
    }

    bool CanLookDoor(PlayerBase player, int index) {
        return HasPlayerAccess(player);
    }

    bool CanRaidDoor(PlayerBase player, int index) {
        return !HasPlayerAccess(player);
    }

    override void OnStoreSave(ParamsWriteContext ctx){
		super.OnStoreSave(ctx);

        Param3<int, ref array<string>, string> store = new Param3<int, ref array<string>, string>(dzlCarId, playerAccess, ownerId);
        ctx.Write(store);
//        Param1<string> store2 = new Param1<string>(ownerName);
//        ctx.Write(store2);
	}

	override bool IsInventoryVisible() {
	    PlayerBase player = PlayerBaseHelper.GetPlayer();
	    
	    return super.IsInventoryVisible() && HasPlayerAccess(player);
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

//        Param1<string> store2 = new Param1<string>("");
//        if (ctx.Read(store2)){
//            ownerName = store2.param1;
//        }

        DebugMessageDZL("playerAccess " + playerAccess.Count());
        DebugMessageDZL("dzlCarId " + dzlCarId);
        DebugMessageDZL("ownerId " + ownerId);
//        DebugMessageDZL("ownerName " + ownerName);
        DebugMessageDZL("position " + GetPosition().ToString(true));

        SynchronizeValues(null);
		return true;
	}

	void SynchronizeValues(PlayerIdentity sender) {
	    if (sender && ownerId == "") {
	        ownerId = sender.GetId();
	        ownerName = sender.GetName();
	    }
//
//        if (sender && ownerName == "" && ownerId == sender.GetId()) {
//	        ownerName = sender.GetName();
//	    }

        GetGame().RPCSingleParam(this, DAY_Z_LIFE_UPDATE_CAR, new Param5<CarScript, int, ref array<string>, string, string>(this, dzlCarId, playerAccess, ownerId, ownerName), true, sender);
    }
}
