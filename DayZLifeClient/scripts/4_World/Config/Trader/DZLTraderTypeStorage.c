class DZLTraderTypeStorage {
    private string type;
    private string fileName;
    private float currentStorage = 0;
    private int lastTick;
    private int reducePerTick;
    private int tickLengthInMinutes;
    private int maxStorage;
    [NonSerialized()]private bool mustSave = false;

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

    string GetType() {
        return type;
    }

    bool IsType(string _type) {
        return this.type == _type;
    }

    void StorageDown() {
        currentStorage--;
        mustSave = true;
    }

    bool IsStorageBelowZero() {
        return currentStorage < 0;
    }

    bool IsStorageFull() {
        return maxStorage <= currentStorage;
    }

    bool IsStorageOverFilled() {
        return maxStorage < currentStorage;
    }

    bool IsStorageEmpty() {
        return currentStorage == 0;
    }

    void StorageUp(float downValue) {
        currentStorage = currentStorage + downValue;
        mustSave = true;
    }

    float getStorage() {
        return currentStorage;
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
        if(GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_ITEM_STORAGE + fileName)) {
            JsonFileLoader<DZLTraderTypeStorage>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_ITEM_STORAGE + fileName, this);
            return true;
        }
        return false;
    }

    void Save() {
        if(GetGame().IsServer() && mustSave == true) {
            mustSave = false;
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_ITEM_STORAGE);
            DZLJsonFileHandler<DZLTraderTypeStorage>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_ITEM_STORAGE + fileName, this);
        }
    }
}