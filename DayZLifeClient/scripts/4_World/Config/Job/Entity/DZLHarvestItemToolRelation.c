class DZLHarvestItemToolRelation {
    ref array<string> itemsThatCanHarvest;
    ref array<string> itemsThatNeededForHarvest;

    void DZLHarvestItemToolRelation(array<string> itemsThatCanHarvest, array<string> itemsThatNeededForHarvest) {
        this.itemsThatCanHarvest = itemsThatCanHarvest;
        this.itemsThatNeededForHarvest = itemsThatNeededForHarvest;
    }
}