class DZLTraderLocationBuilder: DZLLicenceLocationBuilder {

    override static void Create() {
        DZLTraderPositionCollection config = new DZLTraderPositionCollection;
		array<ref DZLTraderPosition> positions = config.positions;
		
		foreach(DZLTraderPosition position: positions) {
           PlayerBase trader = DZLTraderLocationBuilder.CreatePositions(position, false, false, true, false);
        }
	}
};