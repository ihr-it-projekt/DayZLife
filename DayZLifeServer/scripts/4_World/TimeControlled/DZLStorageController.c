class DZLStorageController {
    void Check() {
        ref array<ref DZLTraderTypeStorage> storageItems = DZLDatabaseLayer.Get().GetTraderStorage().GetStorageItems();
        foreach(DZLTraderTypeStorage itemStorage: storageItems) {
            itemStorage.IncreaseTick();
            if(itemStorage.MustReduce()) {
                itemStorage.ResetTick();
                itemStorage.ReduceTickAmount();
            }
            itemStorage.Save();
        }
    }
}
