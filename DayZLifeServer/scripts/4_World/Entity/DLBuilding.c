class DLBuilding {

    private Building building;
    private ref DLHouse house;

    void DLBuilding(Building building) {
        this.building = building;
        house = new DLHouse(building);
    }

    bool HasOwner() {
        return house.owner != "";
    }

    bool IsOwner(PlayerBase player) {
        return house.owner == player.GetIdentity().GetId();
    }

    void Buy(PlayerBase player) {
        house.AddOwner(player);
        ref DLPlayerHouse playerHouse = new DLPlayerHouse(player);
        playerHouse.AddHouse(house);
    }
}