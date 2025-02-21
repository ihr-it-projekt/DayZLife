class DZLInsuranceManager {
    private static ref DZLInsuranceManager manager;

    private ref map<int, ref DZLCarStoreItem> cars;
    private ref map<int, CarScript> scriptCars;
    private ref map<int, string> ownerIds;

    void DZLInsuranceManager() {
        cars = new map<int, ref DZLCarStoreItem>;
        scriptCars = new map<int, CarScript>;
        ownerIds = new map<int, string>;
    }

    static DZLInsuranceManager Get() {
        if(!manager) {
            manager = new DZLInsuranceManager;
        }
        return manager;
    }

    ref DZLCarStoreItem AddCar(CarScript car, DZLCarStoreItem storeItem) {
        if(car.ownerId != "" && car.dzlCarId && !cars.Contains(car.dzlCarId)) {
            cars.Set(car.dzlCarId, storeItem);
            scriptCars.Set(car.dzlCarId, car);
            ownerIds.Set(car.dzlCarId, car.ownerId);
            return storeItem;
        }
        return null;
    }

    void RemoveCar(CarScript car) {
        if(cars.Contains(car.dzlCarId)) {
            cars.Remove(car.dzlCarId);
            scriptCars.Remove(car.dzlCarId);
            ownerIds.Remove(car.dzlCarId);
        }
    }

    void Check() {
        array<int> carsToRemove = new array<int>;

        foreach(int carId, CarScript car: scriptCars) {
            if(!car) {
                DZLCarStoreItem carStoreItem = cars.Get(carId);
                if(!carStoreItem) continue;
                string ownerId = ownerIds.Get(carId);
                if(ownerId == "") continue;

                DZLStoragePosition storagePosition = DZLConfig.Get().carConfig.GetStorageByPosition(carStoreItem.positionOfStore);
                DZLCarStorage storageIn = DZLDatabaseLayer.Get().GetPlayerCarStorage(ownerId);

                storageIn.AddDZLCarStoreItem(carStoreItem);
                DZLLogStore(ownerId, "car deleted insurance store in", carStoreItem.type, storagePosition.position);
                carsToRemove.Insert(carId);
            } else if(car.CheckHealth()) {
                carsToRemove.Insert(carId);
            }
        }

        foreach(int id: carsToRemove) {
            cars.Remove(id);
            scriptCars.Remove(id);
            ownerIds.Remove(id);
        }
    }
}
