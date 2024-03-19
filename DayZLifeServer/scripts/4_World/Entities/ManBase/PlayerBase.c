modded class PlayerBase {
    override bool OnStoreLoad(ParamsReadContext ctx, int version) {
        bool isOkay = super.OnStoreLoad(ctx, version);
        if(!isOkay) return false;

        dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(GetPlayerId());
        if(dzlPlayer) dzlPlayer.player = this;

        return true;
    }

    override void OnStoreSave(ParamsWriteContext ctx) {
        super.OnStoreSave(ctx);
        dzlPlayer.Save();
    }

    override DZLBank GetBank() {
        return DZLDatabaseLayer.Get().GetBank();
    }

    void Reload() {
        dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(GetPlayerId());
        if(dzlPlayer) dzlPlayer.player = this;
    }

    void TransferFromDeadPlayer(DZLPlayer playerTarget) {
        playerTarget.AddMoneyToPlayer(moneyPlayerIsDead);
        moneyPlayerIsDead = 0;
    }

    private ref DZLLicenceValidator licenceValidator;

    string CanUseLicence(notnull DZLCraftLicence licence) {
        licenceValidator = new DZLLicenceValidator(this, licence);

        return licenceValidator.CanUseLicence();
    }

    void UseLicence(DZLCraftLicence licence) {
        licenceValidator.UseLicence();

        InventoryLocation inventoryLocation = new InventoryLocation;
        EntityAI itemSpawn;
        DZLLicenceCraftedItem itemToCraft = licence.craftedItem;

        if(itemToCraft.spawnOnGround) {
            itemSpawn = SpawnEntityOnGroundPos(itemToCraft.type, itemToCraft.positionIfSpawnOnGround.ToVector());
        } else {
            if(GetInventory().FindFirstFreeLocationForNewEntity(itemToCraft.type, FindInventoryLocationType.ANY, inventoryLocation)) {
                itemSpawn = GetHumanInventory().CreateInInventory(itemToCraft.type);
            } else if(GetHumanInventory().GetEntityInHands()) {
                itemSpawn = GetHumanInventory().CreateInHands(itemToCraft.type);
            } else {
                itemSpawn = SpawnEntityOnGroundPos(itemToCraft.type, GetPosition());
            }
        }

        if(itemSpawn) {
            DZLLogCrafting(GetPlayerId(), "licence crafting get item", itemToCraft.type);
            itemSpawn.SetHealth(itemToCraft.health);
            ItemBase.Cast(itemSpawn).SetQuantity(itemToCraft.quantity);
        }
    }

}