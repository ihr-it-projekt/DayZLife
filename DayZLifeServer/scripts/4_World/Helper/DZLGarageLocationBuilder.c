class DZLGarageLocationBuilder: DZLLicenceLocationBuilder {

    void DZLGarageLocationBuilder() {
        Init();
    }

    override void Create() {
		array<ref DZLStoragePosition> positions = DZLConfig.Get().carConfig.garages;
		
		foreach(DZLStoragePosition position: positions) {
           npcs.Insert(new DZLNPCKeepPosition(CreatePositions(position, false, false, false, false, true)));
        }
	}
};
