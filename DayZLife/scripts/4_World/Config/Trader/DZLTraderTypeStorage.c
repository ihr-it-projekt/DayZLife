class DZLTraderTypeStorage
{
    private string type;
    private string fileName;
    private float currentStorage = 0;
    private int lastTick;
    private int reducePerTick;
    private int tickLengthInMinutes;
    private int maxStorage;

    void DZLTraderTypeStorage(DZLTraderType type) {
        this.type = type.type;
        this.fileName = "typeStorage" + type.type + ".json";
        if (!Load()) {
            currentStorage = 0;
        }

        this.reducePerTick = type.reducePerTick;
        this.tickLengthInMinutes = type.tickLengthInMinutes;
        this.maxStorage = type.maxStorage;

        Save();
    }
	
	string GetType() {
		return type;
	}

    bool IsType(string type) {
        return this.type == type;
    }

    void StorageDown() {
        currentStorage--;
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
    }

    float getStorage() {
        return currentStorage;
    }

    bool MustReduce() {
        return tickLengthInMinutes <= lastTick;
    }

    void IncreaseTick() {
        if (tickLengthInMinutes == 0) return;
        lastTick++;
    }

    void ResetTick() {
        lastTick = 0;
    }

    void ReduceTickAmount() {
        if (currentStorage == 0 || currentStorage == maxStorage || reducePerTick == 0) return;

        currentStorage = currentStorage - reducePerTick;

        if (currentStorage < 0) {
            currentStorage = 0;
        }

        if (currentStorage > maxStorage) {
            currentStorage = maxStorage;
        }

        Save();
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_ITEM_STORAGE + fileName)) {
            JsonFileLoader<DZLTraderTypeStorage>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_ITEM_STORAGE + fileName, this);
            return true;
        }
        return false;
    }

    void Save(){
        if (GetGame().IsServer()) {
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_ITEM_STORAGE);
            DZLJsonFileHandler<DZLTraderTypeStorage>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_ITEM_STORAGE + fileName, this);
        }
    }
}