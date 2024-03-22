modded class DZLTraderTypeStorage {

    void DZLTraderTypeStorage(DZLTraderType _type) {
        this.type = _type.type;
        this.fileName = "typeStorage" + _type.type + ".json";
        if(!Load()) {
            currentStorage = 0;
        }

        this.reducePerTick = _type.reducePerTick;
        this.tickLengthInMinutes = _type.tickLengthInMinutes;
        this.maxStorage = _type.maxStorage;
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

    private bool Load() {
        if(FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_ITEM_STORAGE + fileName)) {
            JsonFileLoader<DZLTraderTypeStorage>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_ITEM_STORAGE + fileName, this);
            return true;
        }
        return false;
    }

    void Save() {
        if(mustSave == true) {
            mustSave = false;
            DZLJsonFileHandler<DZLTraderTypeStorage>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_ITEM_STORAGE + fileName, this);
        }
    }
}