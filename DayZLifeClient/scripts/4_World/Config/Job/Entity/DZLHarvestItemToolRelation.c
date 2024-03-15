class DZLHarvestItemToolRelation {
    ref array<string> itemsThatCanHarvest;
    ref array<string> itemsThatNeededForHarvest;

    void DZLHarvestItemToolRelation(array<string> _itemsThatCanHarvest, array<string> _itemsThatNeededForHarvest) {
        this.itemsThatCanHarvest = _itemsThatCanHarvest;
        this.itemsThatNeededForHarvest = _itemsThatNeededForHarvest;
    }
}