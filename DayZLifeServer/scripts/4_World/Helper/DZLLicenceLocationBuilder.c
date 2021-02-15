class DZLLicenceLocationBuilder
 {
    void Create() {
		array<ref DZLLicencePosition> positions = DZLConfig.Get().licenceConfig.positionOfLicencePoints;
		foreach(DZLLicencePosition position: positions) {
		    DZLBaseActionObject object = CreatePositions(position, "DZLLicenseActionObject");
		}
	}

	DZLBaseActionObject CreatePositions(DZLLicencePosition position, string type) {
        Object object = DZLSpawnHelper.SpawnActionPoint(position.position, position.orientation, type);
        return DZLBaseActionObject.Cast(object);
	}
}
