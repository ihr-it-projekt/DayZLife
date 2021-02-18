class DZLLicenceLocationBuilder
 {
    void Create() {
		array<ref DZLLicencePosition> positions = DZLConfig.Get().licenceConfig.positionOfLicencePoints;
		foreach(DZLLicencePosition position: positions) {
		    CreatePositions(position, "DZLLicenseActionObject");
		}

        array<ref DZLLicence> licencePositions = DZLConfig.Get().licenceConfig.licences.collection;
        foreach(DZLLicence licencePosition: licencePositions) {
            CreatePositionsLicence(licencePosition, "DZLLicenceCraftingActionObject");
        }
	}

	DZLBaseActionObject CreatePositions(DZLLicencePosition position, string type) {
        Object object = DZLSpawnHelper.SpawnActionPoint(position.position, position.orientation, type);
        return DZLBaseActionObject.Cast(object);
	}

	DZLBaseActionObject CreatePositionsLicence(DZLLicence position, string type) {
	    if (!position.orientation) position.orientation = "0 0 0";
        Object object = DZLSpawnHelper.SpawnActionPoint(position.position, position.orientation, type);
        return DZLBaseActionObject.Cast(object);
	}
}
