modded class CarScript
{
    string lastDriverId = "";
    bool isSold = false;
	int dzlCarId = 0;
    ref array<string> playerAccess;
    string ownerId = "";
    string ownerName = "";
    bool isSync = false;
    bool isRaided = false;

    private int timeAskForDataSync;

    private ref Timer carCheckTimer;
	private bool hasInsurance = false;
	private bool hasInsuranceServer = false;
	private vector lastGaragePosition = "0 0 0";


    override void OnEngineStart() {
        super.OnEngineStart();
        Human player = CrewMember(DayZPlayerConstants.VEHICLESEAT_DRIVER);
        if (player) {
            lastDriverId = player.GetIdentity().GetId();
        }
	}

	vector GetLastStoragePosition() {
	    return lastGaragePosition;
	}

	void EnableInsurance(vector lastGaragePosition) {
	    hasInsurance = true;
	    hasInsuranceServer = true;
	    carCheckTimer = new Timer;
        carCheckTimer.Run(10, this, "CheckHealth", null, true);
        this.lastGaragePosition = lastGaragePosition;
		DZLInsuranceManager.Get().AddCar(this);
	}

	void EnableInsuranceClient(bool hasInsurance) {
	    this.hasInsurance = hasInsurance;
	}
	
	bool HasInsurance() {
		return hasInsurance;
	}

	void DisableInsurance() {
	    hasInsurance = false;
	    hasInsuranceServer = false;
	    carCheckTimer.Stop();
		DZLInsuranceManager.Get().RemoveCar(this);
	}

	void CheckHealth() {
        if (GetGame().IsServer()) {
			if (IsRuined()) {
				DisableInsurance();
				DZLStoragePosition storagePosition = DZLConfig.Get().carConfig.GetStorageByPosition(lastGaragePosition);
				
				DZLCarStorage storageIn = DZLDatabaseLayer.Get().GetPlayerCarStorage(ownerId);
				
				storageIn.Add(this, storagePosition.position, true);
                DZLLogStore(ownerId, "insurance store in", GetType(), storagePosition.position);
			}
		}
	}


	override void SetActions(){
	    super.SetActions();

        AddAction(DZLActionOpenCarMenu);
        AddAction(ActionGetOwnerName);
        AddAction(ActionGetInsurance);
        AddAction(DZLActionRaidCar);
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

		SetAllowDamage(true);

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
    	    GetGame().RPCSingleParam(this, DAY_Z_LIFE_UPDATE_CAR_FROM_PLAYER_SIDE, null, true);
			timeAskForDataSync = currentDate.inSeconds;
    	}

        if (!player) return false;
		
		string ident = player.GetPlayerId();
		
		DZLPlayer dzlPlayer = player.GetDZLPlayer();

		if (!dzlPlayer) return false;

        return isRaided || ident == ownerId || -1 != playerAccess.Find(ident) || dzlPlayer.IsActiveAsCop();
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

    bool CanRaidDoor(PlayerBase player) {
        return !HasPlayerAccess(player);
    }

    override void OnStoreSave(ParamsWriteContext ctx){
		super.OnStoreSave(ctx);

        Param3<int, ref array<string>, string> store = new Param3<int, ref array<string>, string>(dzlCarId, playerAccess, ownerId);
        ctx.Write(store);
        Param1<string> store2 = new Param1<string>(ownerName);
        ctx.Write(store2);
        Param2<bool, vector> param3 = new Param2<bool, vector>(hasInsuranceServer, lastGaragePosition);
        ctx.Write(param3);
	}

	override bool IsInventoryVisible() {
	    PlayerBase player = PlayerBaseHelper.GetPlayer();
	    
	    return super.IsInventoryVisible() && HasPlayerAccess(player);
    }

	override bool OnStoreLoad(ParamsReadContext ctx, int version){
		if (!super.OnStoreLoad( ctx, version))
			return false;

        autoptr Param3<int, ref array<string>, string> store = new Param3<int, ref array<string>, string>(0, new array<string>, "");
        if (ctx.Read(store)){
            dzlCarId = store.param1;
            playerAccess = store.param2;
            ownerId = store.param3;
        }

        autoptr Param1<string> store2 = new Param1<string>("");
        if (ctx.Read(store2)){
            ownerName = store2.param1;
        }

        autoptr Param2<bool, vector> store3 = new Param2<bool, vector>(false, "0 0 0");
        if (ctx.Read(store3)){
			hasInsuranceServer = store3.param1;
            if (hasInsuranceServer) {
                EnableInsurance(store3.param2);
				DZLInsuranceManager.Get().AddCar(this);
            }
        }

	
        SynchronizeValues(null);
		
		return true;
	}

	void SynchronizeValues(PlayerIdentity sender) {
	    if (sender && ownerId == "") {
	        ownerId = sender.GetId();
	        ownerName = sender.GetName();
	    }

        if (sender && ownerName == "" && ownerId == sender.GetId()) {
	        ownerName = sender.GetName();
	    }

        GetGame().RPCSingleParam(this, DAY_Z_LIFE_UPDATE_CAR, new Param6<int, ref array<string>, string, string, bool, bool>(dzlCarId, playerAccess, ownerId, ownerName, isRaided, hasInsurance), true, sender);
    }

	override void OnContact( string zoneName, vector localPos, IEntity other, Contact data ){
	    bool carCollisionDamage = true;
	    if (GetGame().IsServer()) {
			carCollisionDamage = DZLConfig.Get().carConfig.carCollisionDamage;
	    } else {
	        PlayerBase player = PlayerBaseHelper.GetPlayer();
			carCollisionDamage = player.config.carConfig.carCollisionDamage;
	    }
		
		if (carCollisionDamage) {
			super.OnContact(zoneName, localPos, other, data);
		}
    }

}
