class DZLTuningListener: DZLBaseEventListener {

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.EVENT_TUNE_CAR) {
            autoptr Param1<string> paramTuneCar;
            CarScript car = CarScript.Cast(target);
            if(!car) return;


            if(car.IsRuined()) {
                DZLSendMessage(sender, "#car_can_not_tuned_is_ruined");
                return;
            }

            if(!ctx.Read(paramTuneCar) || !paramTuneCar.param1) return;

            CargoBase cargo = car.GetInventory().GetCargo();

            vector carPosition = car.GetPosition();
            vector carHeading = car.GetOrientation();
            vector lastStoragePosition = car.GetLastStoragePosition();
            bool hasInsurance = car.hasInsurance;

            DZLCarStoreItem storedCar = new DZLCarStoreItem(car, "0 0 0", true, false);

            DZLTuningConfig config = DZLConfig.Get().tuningConfig;
            DZLCarTuneConfig before = config.GetOptionByType(storedCar.type);
            if(!before) return;

            DZLCarTuneConfig after = config.GetOptionByType(paramTuneCar.param1);
            if(!after) return;

            ReplaceTuningTypes(before, after, storedCar);

            DZLInsuranceManager.Get().RemoveCar(car);
            GetGame().ObjectDelete(car);

            CarScript carSpawned = SpawnCar(sender, storedCar, carPosition, carHeading, lastStoragePosition, hasInsurance);

            if(!carSpawned) return;
            if(hasInsurance) DZLInsuranceManager.Get().AddCar(carSpawned, null);
        }
    }

    private void ReplaceTuningTypes(DZLCarTuneConfig tuneConfigBefore, DZLCarTuneConfig tuneConfigAfter, DZLCarStoreItem itemInStock) {
        itemInStock.type = tuneConfigAfter.type;

        foreach(CarTuneAttachment tuneAttachmentBefore: tuneConfigBefore.tunedAttachments) {
            foreach(CarTuneAttachment tuneAttachmentAfter: tuneConfigAfter.tunedAttachments) {
                if(!tuneAttachmentAfter.IsForSamePosition(tuneAttachmentBefore)) continue;
                foreach(DZLStoreItem orgAttachment: itemInStock.attached) {
                    if(orgAttachment.type != tuneAttachmentBefore.type) continue;
                    orgAttachment.type = tuneAttachmentAfter.type;
                    break;
                }
            }
        }
    }

    private CarScript SpawnCar(PlayerIdentity sender, DZLCarStoreItem itemInStock, vector position, vector orientation, vector lastStoragePosition, bool enableInsurance) {
        CarScript car;

        InventoryLocation il = new InventoryLocation;
        vector mat[4];
        Math3D.MatrixIdentity4(mat);
        mat[3] = position;
        il.SetGround(NULL, mat);
        EntityAI item = SpawnEntity(itemInStock.type, il, ECE_PLACE_ON_SURFACE, RF_DEFAULT);

        if(!item) return null;
        car = CarScript.Cast(item);

        if(!car) return null;
        array<ref DZLStoreItem> attached = itemInStock.attached;
        bool spawnOnGround = false;
        foreach(DZLStoreItem attach: attached) {
            if(DZLSpawnHelper.Add(car, attach) && !spawnOnGround) {
                spawnOnGround = true;
            }
        }

        if(spawnOnGround) {
            DZLSendMessage(sender, "#car_was_tuned_some_items_can_not_placed_in_car");
        } else {
            DZLSendMessage(sender, "#car_was_tuned");
        }

        if(enableInsurance) car.EnableInsurance(lastStoragePosition);

        car.OwnCar(null, itemInStock.ownerId, itemInStock.ownerName);
        car.UpdatePlayerAccess(itemInStock.playerAccess);
        car.SetOrientation(orientation);

        FillFluid(car, CarFluid.FUEL, itemInStock.fuel);
        FillFluid(car, CarFluid.OIL, itemInStock.oil);
        FillFluid(car, CarFluid.BRAKE, itemInStock.brake);
        FillFluid(car, CarFluid.COOLANT, itemInStock.coolant);
        FillFluid(car, CarFluid.USER1, itemInStock.user1);
        FillFluid(car, CarFluid.USER2, itemInStock.user2);
        FillFluid(car, CarFluid.USER3, itemInStock.user3);
        FillFluid(car, CarFluid.USER4, itemInStock.user4);

        return car;
    }

    private void FillFluid(CarScript car, int type, float inPercent) {
        if(inPercent <= 0) return;
        car.Fill(type, car.GetFluidCapacity(type) * inPercent);
    }

    private void SendStorageUpdate(PlayerIdentity sender) {
        DZLCarStorage playerStorage = DZLDatabaseLayer.Get().GetPlayerCarStorage(sender.GetId());
        DZLCarStorage fractionStorage;
        DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(sender.GetId());

        if(dzlPlayer.IsInAnyFraction()) {
            DZLFractionMember member = dzlPlayer.GetFractionMember();
            if(member) fractionStorage = DZLDatabaseLayer.Get().GetFractionCarStorage(member.fractionID);
        }

        GetGame().RPCSingleParam(null, DZL_RPC.EVENT_GET_CAR_DATA_FROM_STORAGE_RESPONSE, new Param2<ref DZLCarStorage, ref DZLCarStorage>(playerStorage, fractionStorage), true, sender);
    }
}
