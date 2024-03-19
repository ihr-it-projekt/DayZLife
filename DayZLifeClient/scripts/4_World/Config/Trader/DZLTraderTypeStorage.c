class DZLTraderTypeStorage {
    private string type;
    private string fileName;
    private float currentStorage = 0;
    private int lastTick;
    private int reducePerTick;
    private int tickLengthInMinutes;
    private int maxStorage;
    [NonSerialized()]private bool mustSave = false;

    string GetType() {
        return type;
    }

    bool IsType(string _type) {
        return this.type == _type;
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

    float getStorage() {
        return currentStorage;
    }
    void StorageDown() {
        currentStorage--;
    }

    void StorageUp(float downValue) {
        currentStorage = currentStorage + downValue;
    }
}