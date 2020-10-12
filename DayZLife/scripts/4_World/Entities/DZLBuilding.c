class DZLBuilding {

    private Building building;
    private ref DZLHouse house;

    void DZLBuilding(Building building) {
        this.building = building;
        house = new DZLHouse(building);
    }

    bool HasOwner() {
        return house.owner != "";
    }

    bool IsOwner(PlayerBase player) {
        return house.owner == player.GetIdentity().GetId();
    }

    void Buy(PlayerBase player) {
        house.AddOwner(player);
        ref DZLPlayerHouse playerHouse = new DZLPlayerHouse(player);
        playerHouse.AddHouse(house);
    }
}