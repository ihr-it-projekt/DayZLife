class DZLObjectFinder {

    static CarScript GetCar(vector carSpawnPosition, vector orientation, string carType, DZLPlayer player, bool byOwner = false) {
        array<Object> excludedObjects = new array<Object>;
        array<Object> nearbyObjects = new array<Object>;
        if(GetGame().IsBoxColliding(carSpawnPosition, orientation, "10 10 10", excludedObjects, nearbyObjects)) {
            foreach(Object object: nearbyObjects) {
                if(object.GetType() == carType) {
                    CarScript carsScript = CarScript.Cast(object);
                    if(!carsScript) continue;

                    if(!byOwner) {
                        if(player.IsInAnyFraction() && (player.GetFraction() && !player.GetFraction().HasMember(carsScript.ownerId))) {
                            continue;
                        } else if(!player.IsInAnyFraction() && carsScript.ownerId != player.dayZPlayerId) {
                            continue;
                        }
                    } else {
                        if(carsScript.ownerId != player.dayZPlayerId) continue;
                    }

                    return carsScript;
                }
            }
        }

        return null;
    }

    static CarScript GetCarForTuning(vector carSpawnPosition, string carType) {
        array<Object> excludedObjects = new array<Object>;
        array<Object> nearbyObjects = new array<Object>;
        if(GetGame().IsBoxColliding(carSpawnPosition, "0 0 0", "3 5 9", excludedObjects, nearbyObjects)) {
            foreach(Object object: nearbyObjects) {
                if(object.GetType().Contains(carType)) {
                    CarScript carsScript = CarScript.Cast(object);
                    if(!carsScript) continue;

                    return carsScript;
                }
            }
        }

        return null;
    }
}
