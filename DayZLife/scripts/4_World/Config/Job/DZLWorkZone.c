class DZLWorkZone
{
    vector position;
    float range;
    string zoneType;
    int timeToHarvestPerItemInSeconds;
    int damagePerHarvestItem;
    ref array<ref DZLHarvestItemToolRelation> harvestItemToolRelation;

    void DZLWorkZone(vector position, float range, string zoneDisplayName, string zoneType, int timeToHarvestPerItemInSeconds, int damagePerHarvestItem, array<ref DZLHarvestItemToolRelation> harvestItemToolRelation) {
        this.position = position;
        this.range = range;
        this.zoneType = zoneType;
        this.timeToHarvestPerItemInSeconds = timeToHarvestPerItemInSeconds;
        this.harvestItemToolRelation = harvestItemToolRelation;
    }
}
