class DZLGarageLocationBuilder: DZLLicenceLocationBuilder {

    override static void Create() {
		array<ref DZLStoragePosition> positions = DZLConfig.Get().carConfig.garages;
		
		foreach(DZLStoragePosition position: positions) {
           PlayerBase trader = DZLGarageLocationBuilder.CreatePositions(position, false, false, false, false, true);
        }
	}
};
