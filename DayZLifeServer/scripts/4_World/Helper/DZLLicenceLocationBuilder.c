class DZLLicenceLocationBuilder
 {
    void Create() {
		array<ref DZLLicencePosition> positions = DZLConfig.Get().licenceConfig.positionOfLicencePoints;
		foreach(DZLLicencePosition position: positions) {
		    DZLBaseActionObject object = CreatePositions(position);
		    object.EnableLicensePoint();
		}
	}

	DZLBaseActionObject CreatePositions(DZLLicencePosition position) {
        Object object = DZLSpawnHelper.SpawnActionPoint(position.position, position.orientation, position.type);
        return DZLBaseActionObject.Cast(object);
	}
}
