class DZLTraderStorage
{
    private ref array<ref DZLTraderTypeStorage> storage;

    void DZLTraderStorage() {
        storage = new array<ref DZLTraderTypeStorage>;
    }

    void Insert(DZLTraderType item) {
        storage.Insert(new DZLTraderTypeStorage(item));
    }

    ref array<ref DZLTraderTypeStorage> GetStorageItems() {
        return storage;
    }

    DZLTraderTypeStorage GetCurrentStorageByName(string name) {
       if (storage) {
			foreach(DZLTraderTypeStorage itemStorage: storage) {
				if (name == itemStorage.GetType()) {
					return itemStorage;
				}
			}
		}
		
		return null;	
    }
}