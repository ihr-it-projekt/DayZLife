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

    void DZLWorkZone(int _m_CommandUID, vector _position, float _range, string _zoneDisplayName, int _timeToHarvestPerItemInSeconds, int _damagePerHarvestItem, array<ref DZLHarvestItemToolRelation> _harvestItemToolRelation, bool _isLegalJob = true) {
        this.zoneDisplayName = _zoneDisplayName;
        this.m_CommandUID = _m_CommandUID;
        this.position = _position;
        this.range = _range;
        this.timeToHarvestPerItemInSeconds = _timeToHarvestPerItemInSeconds;
        this.harvestItemToolRelation = _harvestItemToolRelation;
        this.isLegalJob = _isLegalJob;
        this.showNotOnMapInAlmanac = false;
    }
}
