modded class CarScript {
    string lastDriverId = "";
    bool isSold = false;
    int dzlCarId = 0;
    ref array<string> playerAccess;
    string ownerId = "";
    string ownerName = "";
    bool isSync = false;
    bool isRaided = false;

    private int timeAskForDataSync;

    private bool hasInsurance = false;
    private bool hasInsuranceServer = false;
    private vector lastGaragePosition = "0 0 0";
    private ref DZLCarStoreItem carStoreItem;


    override void OnEngineStart() {
        super.OnEngineStart();
        Human player = CrewMember(DayZPlayerConstants.VEHICLESEAT_DRIVER);
        if(player) {
            lastDriverId = player.GetIdentity().GetId();
        }
    }

    vector GetLastStoragePosition() {
        return lastGaragePosition;
    }

    void EnableInsurance(vector lastGaragePosition) {
        hasInsurance = true;
        hasInsuranceServer = true;
        this.lastGaragePosition = lastGaragePosition;
        carStoreItem = DZLInsuranceManager.Get().AddCar(this, null);
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
    }

    bool CheckHealth() {
        if(GetGame().IsServer() && IsDamageDestroyed() && hasInsurance) {
            DisableInsurance();
            DZLStoragePosition storagePosition = DZLConfig.Get().carConfig.GetStorageByPosition(lastGaragePosition);

            DZLCarStorage storageIn = DZLDatabaseLayer.Get().GetPlayerCarStorage(ownerId);

            storageIn.Add(this, storagePosition.position, false, true);
            DZLLogStore(ownerId, "insurance store in", GetType(), storagePosition.position);
            return true;
        }

        return false;
    }

    override void SetActions() {
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

    void OwnCar(PlayerIdentity player, string _ownerId, string _ownerName) {
        if(_ownerId != "" && _ownerName != "") {
            this.ownerId = _ownerId;
            this.ownerName = _ownerName;
        } else {
            ownerId = player.GetId();
            ownerName = player.GetName();
        }

        playerAccess = new array<string>;
        SynchronizeValues(null);
    }

    void ChangeOwner(DZLPlayer player) {
        ownerId = player.dayZPlayerId;
        ownerName = player.playerName;
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

    void UpdatePlayerAccessByDZLOnlinePlayer(array<DZLOnlinePlayer> onlinePlayers) {
        this.playerAccess = new array<string>;

        foreach(DZLOnlinePlayer player: onlinePlayers) {
            this.playerAccess.Insert(player.id);
        }
        this.playerAccess = playerAccess;
        SynchronizeValues(null);
    }

    void UpdatePlayerAccess(array<string> playerAccess) {
        this.playerAccess = playerAccess;

        SynchronizeValues(null);
    }

    bool HasPlayerAccess(PlayerBase player) {
        DZLDate currentDate = new DZLDate();
        if(GetGame().IsClient() && currentDate.inSeconds - timeAskForDataSync > 5 && !isSync) {
            GetGame().RPCSingleParam(this, DAY_Z_LIFE_UPDATE_CAR_FROM_PLAYER_SIDE, null, true);
            timeAskForDataSync = currentDate.inSeconds;
        }

        if(!player) return false;

        string ident = player.GetPlayerId();

        DZLPlayer dzlPlayer = player.GetDZLPlayer();

        if(!dzlPlayer) return false;

        return isRaided || ident == ownerId || -1 != playerAccess.Find(ident) || dzlPlayer.IsActiveAsCop() || player.GetConfig().adminIds.CanManageCars(ident) || dzlPlayer.IsActiveAsArmy();
    }

    void RemovePlayerAccess(string ident) {
        int index = playerAccess.Find(ident);
        if(index != -1) {
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

    override void OnStoreSave(ParamsWriteContext ctx) {
        super.OnStoreSave(ctx);

        Param3<int, ref array<string>, string> store = new Param3<int, ref array<string>, string>(dzlCarId, playerAccess, ownerId);
        ctx.Write(store);
        Param1<string> store2 = new Param1<string>(ownerName);
        ctx.Write(store2);
        Param2<bool, vector> param3 = new Param2<bool, vector>(hasInsuranceServer, lastGaragePosition);
        ctx.Write(param3);
        Param1<ref DZLCarStoreItem> store4 = new Param1<ref DZLCarStoreItem>(carStoreItem);
        ctx.Write(store4);
    }

    override bool IsInventoryVisible() {
        PlayerBase player = DZLPlayerBaseHelper.GetPlayer();

        return super.IsInventoryVisible() && HasPlayerAccess(player);
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version) {
        if(!super.OnStoreLoad(ctx, version))
            return false;

        autoptr Param3<int, ref array<string>, string> store = new Param3<int, ref array<string>, string>(0, new array<string>, "");
        if(ctx.Read(store)) {
            dzlCarId = store.param1;
            playerAccess = store.param2;
            ownerId = store.param3;
        }

        autoptr Param1<string> store2 = new Param1<string>("");
        if(ctx.Read(store2)) {
            ownerName = store2.param1;
        }

        autoptr Param2<bool, vector> store3 = new Param2<bool, vector>(false, "0 0 0");
        if(ctx.Read(store3)) {
            hasInsuranceServer = store3.param1;
            if(hasInsuranceServer) {
                EnableInsurance(store3.param2);
            }
        }

        Param1<ref DZLCarStoreItem> store4 = new Param1<ref DZLCarStoreItem>(null);
        if(ctx.Read(store4) && store4.param1) {
            carStoreItem = store4.param1;
            DZLInsuranceManager.Get().AddCar(this, carStoreItem);
        }

        SynchronizeValues(null);

        return true;
    }

    void SynchronizeValues(PlayerIdentity sender) {
        if(sender && ownerId == "") {
            ownerId = sender.GetId();
            ownerName = sender.GetName();
        }

        if(sender && ownerName == "" && ownerId == sender.GetId()) {
            ownerName = sender.GetName();
        }

        GetGame().RPCSingleParam(this, DAY_Z_LIFE_UPDATE_CAR, new Param6<int, ref array<string>, string, string, bool, bool>(dzlCarId, playerAccess, ownerId, ownerName, isRaided, hasInsurance), true, sender);
    }

    override void OnContact(string zoneName, vector localPos, IEntity other, Contact data) {
        bool carCollisionDamage = true;
        if(GetGame().IsServer()) {
            carCollisionDamage = DZLConfig.Get().carConfig.carCollisionDamage;
        } else {
            PlayerBase player = DZLPlayerBaseHelper.GetPlayer();
            carCollisionDamage = player.GetConfig().carConfig.carCollisionDamage;
        }

        if(carCollisionDamage) {
            super.OnContact(zoneName, localPos, other, data);
        }
    }

}
