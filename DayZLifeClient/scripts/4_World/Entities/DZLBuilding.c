class DZLBuilding {

    private Building building;
    private ref DZLHouse house;

    void DZLBuilding(Building building) {
        this.building = building;
        house = DZLDatabaseLayer.Get().GetHouse(building);
    }

    bool HasOwner() {
        return house.HasOwner();
    }

    bool IsOwner(PlayerBase player) {
        return house.IsOwner(player);
    }

    void BuyOnServer(PlayerBase player) {
        if(!GetGame().IsClient()) {
            house.AddOwner(player);
            DZLPlayerHouse playerHouse = DZLDatabaseLayer.Get().GetPlayerHouse(player.GetPlayerId());
            playerHouse.AddHouse(house);
        }
    }
    void SellOnServer(PlayerBase player) {
        if(!GetGame().IsClient()) {
            house.RemoveOwner();
            if (house.HasInventory()) {
                DZLDatabaseLayer.Get().RemoveHouseInventory(house.GetOwner(), house.GetPosition());
            }
            house.DisableInventory();
            ref DZLPlayerHouse playerHouse = DZLDatabaseLayer.Get().GetPlayerHouse(player.GetPlayerId());
            playerHouse.RemoveKey(house);

        }
    }

    void BuyStorageOnServer(ref DZLStorageTypeBought storage) {
        if(!GetGame().IsClient()) {
            house.AddStorage(storage);
        }
    }

    void SellStorageOnServer(DZLStorageTypeBought storage) {
        if(!GetGame().IsClient()) {
            house.RemoveStorage(storage);
        }
    }

    bool HasAlarmSystem() {
        return house.HasAlarmSystem();
    }

    DZLHouseExtension GetHouseAlarm() {
        return house.GetHouseAlarm();
    }

    bool CanBuyAlarm(DZLHouseExtension alarm) {
        if (house.HasAlarmSystem() && alarm.level == house.GetHouseAlarm().level + 1) {
            return true;
        } else if (!house.HasAlarmSystem() && alarm.level == 1) {
            return true;
        }

        return false;
    }

    bool CanBuyInventoryExtensionServer(DZLHouseDefinition config) {
        if (house.HasInventory()) {
            if (GetGame().IsServer()) {
                DZLHouseInventory inventory = DZLDatabaseLayer.Get().GetHouseInventory(house.GetOwner(), house.GetPosition());
                if (inventory.GetLevel(config.inventoryItemsPerLevel) >= config.maxHouseInventoryLevel) {
                    return false;
                }
            }
        }
        return true;
    }

    bool CanBuyInventoryExtensionClient(DZLHouseDefinition config, DZLHouseInventory inventory) {
        if (house.HasInventory()) {
            if (GetGame().IsClient()) {
                if (inventory && inventory.GetLevel(config.inventoryItemsPerLevel) >= config.maxHouseInventoryLevel) {
                    return false;
                }
            }
        }
        return true;
    }


    void SetHouseAlarm(DZLHouseExtension houseAlarm) {
        if(!GetGame().IsClient()) {
            house.SetHouseAlarm(houseAlarm);
        }
    }

    void UpdatePlayerAccess(array<DZLOnlinePlayer> playerAccess) {
        if(!GetGame().IsClient()) {
            house.UpdatePlayerAccess(playerAccess);
        }
    }

    array<string> GetPlayerAccess() {
        return house.GetPlayerAccess();
    }

    bool HasPlayerAccess(string ident) {
        return house.HasPlayerAccess(ident);
    }

    vector GetNextFreeStoragePosition(DZLHouseDefinition definition) {
        return house.GetNextFreeStoragePosition(definition);
    }

    DZLStorageTypeBought FindStorageByPosition(vector position) {
        return house.FindStorageByPosition(position);
    }

    array<ref DZLStorageTypeBought> GetStorage() {
        return house.GetStorage();
    }

    DZLHouse GetDZLHouse() {
        return house;
    }

    string GetOwnerName() {
        return house.GetOwnerName();
    }

    bool HasInventory() {
        return house.HasInventory();
    }

    bool HasLockedDoors() {
        return house.HasLockedDoors();
    }
}
