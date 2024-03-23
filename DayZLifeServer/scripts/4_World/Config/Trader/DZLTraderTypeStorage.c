modded class DZLTraderTypeStorage {

    void DZLTraderTypeStorage(DZLTraderType _type) {
        type = _type.type;
        Init(DAY_Z_LIFE_SERVER_FOLDER_DATA_ITEM_STORAGE, "typeStorage" + type);

        if(!Load()) {
            currentStorage = 0;
        }

        reducePerTick = _type.reducePerTick;
        tickLengthInMinutes = _type.tickLengthInMinutes;
        maxStorage = _type.maxStorage;
        mustSave = true;
        Save();
    }

    override void StorageDown() {
        currentStorage--;
        mustSave = true;
    }

    override void StorageUp(float downValue) {
        currentStorage = currentStorage + downValue;
        mustSave = true;
    }

    bool MustReduce() {
        return tickLengthInMinutes <= lastTick;
    }

    void IncreaseTick() {
        if(tickLengthInMinutes == 0) return;
        lastTick++;
        mustSave = true;
    }

    void ResetTick() {
        lastTick = 0;
        mustSave = true;
    }

    void ReduceTickAmount() {
        if(reducePerTick == 0) return;

        currentStorage = currentStorage - reducePerTick;

        if(currentStorage < 0) {
            currentStorage = 0;
        }

        if(currentStorage > maxStorage) {
            currentStorage = maxStorage;
        }
        mustSave = true;
    }

    override void Save() {
        if(mustSave) {
            super.Save();
        }
    }

    override protected bool Read(FileSerializer ctx) {
        if(!ctx.Read(currentStorage)) return false;
        if(!ctx.Read(lastTick)) return false;
        return true;
    }

    override protected void Write(FileSerializer ctx) {
        ctx.Write(currentStorage);
        ctx.Write(lastTick);
    }
}