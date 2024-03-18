class DZLWorkZone {
    int m_CommandUID;
    vector position;
    float range;
    int timeToHarvestPerItemInSeconds;
    int damagePerHarvestItem;
    ref array<ref DZLHarvestItemToolRelation> harvestItemToolRelation;
    string zoneDisplayName;
    bool isLegalJob;
    bool showNotOnMapInAlmanac = false;

}
