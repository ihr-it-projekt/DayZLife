modded class CarScript {

    private vector lastGaragePosition = "0 0 0";
    private ref DZLCarStoreItem carStoreItem;

    override void EEInit() {
        super.EEInit();

        SetAllowDamage(true);
    }

    override void OnEngineStart() {
        super.OnEngineStart();
        Human player = CrewMember(DayZPlayerConstants.VEHICLESEAT_DRIVER);
        if(!player) return;

        lastDriverId = player.GetIdentity().GetId();

        RPCSingleParam(DZL_RPC.UPDATE_CAR_LAST_DRIVER, new Param1<string>(lastDriverId), true);
    }

    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx) {
        super.OnRPC(sender, rpc_type, ctx);
        switch(rpc_type) {
            case(DZL_RPC.REQUEST_UPDATE_CAR): {
                SynchronizeValues(sender);
                return;
            }
        }
    }

    override void OnStoreSave(ParamsWriteContext ctx) {
        super.OnStoreSave(ctx);

        Param3<int, ref array<string>, string> store = new Param3<int, ref array<string>, string>(dzlCarId, playerAccess, ownerId);
        ctx.Write(store);
        Param1<string> store2 = new Param1<string>(ownerName);
        ctx.Write(store2);
        Param2<bool, vector> param3 = new Param2<bool, vector>(hasInsurance, lastGaragePosition);
        ctx.Write(param3);
        Param1<ref DZLCarStoreItem> store4 = new Param1<ref DZLCarStoreItem>(carStoreItem);
        ctx.Write(store4);
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version) {
        if(!super.OnStoreLoad(ctx, version))
            return false;

        Param3<int, ref array<string>, string> store = new Param3<int, ref array<string>, string>(0, new array<string>, "");
        if(ctx.Read(store)) {
            dzlCarId = store.param1;
            playerAccess = store.param2;
            ownerId = store.param3;
        }

        Param1<string> store2 = new Param1<string>("");
        if(ctx.Read(store2)) {
            ownerName = store2.param1;
        }

        Param2<bool, vector> store3 = new Param2<bool, vector>(false, "0 0 0");
        if(ctx.Read(store3)) {
            hasInsurance = store3.param1;
            if(hasInsurance) EnableInsurance(store3.param2);
        }

        Param1<ref DZLCarStoreItem> store4 = new Param1<ref DZLCarStoreItem>(null);
        if(ctx.Read(store4) && store4.param1) {
            carStoreItem = store4.param1;
            DZLInsuranceManager.Get().AddCar(this, carStoreItem);
        }

        SetSynchDirty();
        SynchronizeValues(null);

        return true;
    }

    bool CheckHealth() {
        if(IsDamageDestroyed() && hasInsurance) {
            DisableInsurance();
            DZLStoragePosition storagePosition = DZLConfig.Get().carConfig.GetStorageByPosition(lastGaragePosition);

            DZLCarStorage storageIn = DZLDatabaseLayer.Get().GetPlayerCarStorage(ownerId);

            storageIn.Add(this, storagePosition.position, false, true);
            DZLLogStore(ownerId, "insurance store in", GetType(), storagePosition.position);
            return true;
        }

        return false;
    }

    void DisableInsurance() {
        hasInsurance = false;
        SetSynchDirty();
    }

    void EnableInsurance(vector _lastGaragePosition) {
        hasInsurance = true;
        this.lastGaragePosition = _lastGaragePosition;
        carStoreItem = DZLInsuranceManager.Get().AddCar(this, new DZLCarStoreItem(this, lastGaragePosition, false, true));
        SetSynchDirty();
    }

    vector GetLastStoragePosition() {
        return lastGaragePosition;
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

    override bool IsOwner(PlayerIdentity player) {
        if(ownerId == "") {
            ownerId = player.GetId();
            ownerName = player.GetName();
            RPCSingleParam(DZL_RPC.UPDATE_CAR_OWNER, new Param2<string, string>(ownerId, ownerName), true);
        }

        return ownerId == player.GetId();
    }

    void UpdatePlayerAccessByDZLOnlinePlayer(array<DZLOnlinePlayer> onlinePlayers) {
        this.playerAccess = new array<string>;

        foreach(DZLOnlinePlayer player: onlinePlayers) {
            this.playerAccess.Insert(player.id);
        }
        this.playerAccess = playerAccess;
        RPCSingleParam(DZL_RPC.UPDATE_CAR_ACCESS, new Param1<ref array<string>>(playerAccess), true);
    }

    void UpdatePlayerAccess(array<string> _playerAccess) {
        this.playerAccess = _playerAccess;
        RPCSingleParam(DZL_RPC.UPDATE_CAR_ACCESS, new Param1<ref array<string>>(playerAccess), true);
    }


    void RemovePlayerAccess(string ident) {
        int index = playerAccess.Find(ident);
        if(index == -1) return;
        playerAccess.Remove(index);
        RPCSingleParam(DZL_RPC.UPDATE_CAR_ACCESS, new Param1<ref array<string>>(playerAccess), true);
    }

    void SynchronizeValues(PlayerIdentity sender) {
        if(sender && ownerId == "") {
            ownerId = sender.GetId();
            ownerName = sender.GetName();
        }

        if(sender && ownerName == "" && ownerId == sender.GetId()) {
            ownerName = sender.GetName();
        }

        RPCSingleParam(DZL_RPC.UPDATE_CAR, new Param3<ref array<string>, string, string>(playerAccess, ownerId, ownerName), true);
    }

    override void OnContact(string zoneName, vector localPos, IEntity other, Contact data) {
        DZLCarConfig carConfig = DZLConfig.Get().carConfig;
        if(!carConfig.carCollisionDamage) return;
        if(carConfig.disallowCarCollisionWhenNoMedicIsOnline && !DZLPlayerArrestListener.instance.medicCount) return;

        super.OnContact(zoneName, localPos, other, data);
    }
}
