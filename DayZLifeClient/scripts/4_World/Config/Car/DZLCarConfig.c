class DZLCarConfig {
    bool carCollisionDamage = false;
    bool disallowCarCollisionWhenNoMedicIsOnline = true;
    bool canStoreCarsWithGoods = false;
    bool canGetCarsFromEveryGarage = true;
    int carRaidTimeInSeconds = 60;
    int chanceToRaid = 2;
    int carInsurancePrice = 2000;
    ref array<ref DZLStoragePosition> garages;
    ref array<string> carTypesToStore;
    ref array<string> carRaidTools;

    string version = "5";

    DZLStoragePosition GetStorageByPosition(vector playerPosition, int distance = 2) {
        if(!playerPosition) {
            return null;
        }

        foreach(DZLStoragePosition position: garages) {
            float distanceToPos = vector.Distance(position.position, playerPosition);
            if(distanceToPos <= distance) {
                return position;
            }
        }

        return null;
    }
}
