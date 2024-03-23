class DZLLicenceLocationBuilder {
    protected ref array<Object> objects = new array<Object>;

    void Create() {
        array<ref DZLLicencePosition> positions = DZLConfig.Get().licenceConfig.positionOfLicencePoints;
        foreach(DZLLicencePosition position: positions) {
            CreatePositions(position, "DZLLicenseActionObject");
        }

        array<ref DZLCraftLicence> licencePositions = DZLConfig.Get().licenceConfig.licenceCollection.collection;
        foreach(DZLCraftLicence licencePosition: licencePositions) {
            CreatePositionsLicence(licencePosition, "DZLLicenceCraftingActionObject");
        }
    }

    void Reload() {
        foreach(Object object: objects) {
            if(object) GetGame().ObjectDelete(object);
        }
        Create();
    }

    DZLBaseActionObject CreatePositions(DZLLicencePosition position, string type) {
        Object object = DZLSpawnHelper.SpawnActionPoint(position.position, position.orientation, type);

        if(object) objects.Insert(object);

        return DZLBaseActionObject.Cast(object);
    }

    DZLBaseActionObject CreatePositionsLicence(DZLCraftLicence position, string type) {
        Object object = DZLSpawnHelper.SpawnActionPoint(position.position, position.orientation, type);
        return DZLBaseActionObject.Cast(object);
    }
}
